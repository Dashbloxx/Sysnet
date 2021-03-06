#!/bin/sh
# $NetBSD: upgrade.sh,v 1.10 2021/08/09 19:24:32 andvar Exp $
#
# Copyright (c) 1994 Christopher G. Demetriou
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. All advertising materials mentioning features or use of this software
#    must display the following acknowledgement:
#          This product includes software developed for the
#          NetBSD Project.  See http://www.NetBSD.org/ for
#          information about NetBSD.
# 4. The name of the author may not be used to endorse or promote products
#    derived from this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 
# <<Id: LICENSE,v 1.2 2000/06/14 15:57:33 cgd Exp>>

#	NetBSD upgrade script.
#	In a perfect world, this would be a nice C program, with a reasonable
#	user interface.

#DONTDOIT=echo

VERSION=1.2

getresp() {
	read resp
	if [ "X$resp" = "X" ]; then
		resp=$1
	fi
}

getvar() {
	echo $(eval $(echo "echo \$$1"))
}

shiftvar() {
	local - var
	var="$1"
	list="$(getvar $var)"
	set -- $list
	shift
	setvar $var "$*"
}

getparts() {
	disklabel $1 2>/dev/null | sed -e '/^[ ][ ][ad-p]/!d' |
	sed -e 's,^[ ]*\([a-p]\):[ ]*[0-9]*[ ]*[0-9]*[ ][ ]*\([a-zA-Z0-9.]*\).*,\1 \2,' |
	sed -e ':a
		N;${s/\n/ /g;p;d;}
		ba'
}

getdrives() {
	local du thispart
	for du in /dev/rsd?a; do
		dd if=$du of=/dev/null bs=1b count=1 >/dev/null 2>&1
		if [ $? -eq 0 ]; then
			thisunit=`echo $du | sed -e 's,/dev/r\(...\)a,\1,g'`
			driveunits="$driveunits $thisunit"
		else
			continue;
		fi
		setvar $thisunit "$(getparts $thisunit)"
		export $thisunit
	done
	export drivenunits
}

Convert_fstab() {
	if [ ! -e /mnt/etc/fstab.ufs ]; then
		mv /mnt/etc/fstab /mnt/etc/fstab.ufs
	fi
	sed "s/ufs/ffs/" /mnt/etc/fstab.ufs >/mnt/etc/fstab
}

echo	"Welcome to the NetBSD ${VERSION} upgrade program."
echo	""
echo	"This program is designed to help you put the new version of NetBSD"
echo	"on your hard disk, in a simple and rational way.  To upgrade, you"
echo	"must have plenty of free space on all partitions which will be"
echo	"upgraded.  If you have at least 1MB free on your root partition,"
echo	"and several free on your /usr partition, you should be fine."
echo	""
echo	"As with anything which modifies your hard drive's contents, this"
echo	"program can cause SIGNIFICANT data loss, and you are advised"
echo	"to make sure your hard drive is backed up before beginning the"
echo	"upgrade process."
echo	""
echo	"Default answers are displayed in brackets after the questions."
echo	"You can hit Control-C at any time to quit, but if you do so at a"
echo	"prompt, you may have to hit return.  Also, quitting in the middle of"
echo	"the upgrade may leave your system in an inconsistent (and unusable)"
echo	"state."
echo	""
echo -n "Proceed with upgrade? [n] "
getresp "n"
case "$resp" in
	y*|Y*)
		echo	"Cool!  Let's get to it..."
		;;
	*)
		echo	""
		echo	"OK, then.  Enter 'halt' at the prompt to halt the"
		echo	"machine.  Once the machine has halted, remove the"
		echo	"floppy and press any key to reboot."
		exit
		;;
esac

# find out what units are possible, and query the user.

getdrives

if [ "X${driveunits}" = "X" ]; then
	echo	"FATAL ERROR:"
	echo	"No disk devices."
	echo	"This is probably a bug in the install disks."
	echo	"Exiting install program."
	exit
fi

echo	""
echo	"The following disks are supported by this upgrade procedure:"
echo	"	"${driveunits}
echo	""
echo	"If your system was previously completely contained within the"
echo	"disks listed above (i.e. if your system didn't occupy any space"
echo	"on disks NOT listed above), this upgrade disk can upgrade your"
echo	"system.  If it cannot, hit Control-C at the prompt."
echo	""
while [ "X${drivename}" = "X" ]; do
	echo -n	"Which disk contains your root partition? "
	getresp
	otherdrives=`echo "${driveunits}" | sed -e s,${resp},,`
	if [ "X${driveunits}" = "X${otherdrives}" ]; then
		echo	""
		echo	"\"${resp}\" is an invalid drive name.  Valid choices"
		echo	"are: "${driveunits}
		echo	""
	else
		drivename=${resp}
	fi
done

echo	""
echo	"Root partition is on ${drivename}a."

echo	""
echo	"If you've still installed 0.9 or earlier on your machine or you"
echo	"haven't upgraded your pre-1.0 filesystems, then you might want to"
echo	"upgrade the filesystem to the version introduced with 1.0."
echo	""
echo	"Would you like to upgrade your file systems to the new file system"
echo -n	"format? [y] "
getresp "y"
case "$resp" in
	n*|N*)
		echo	""
		echo	"You should upgrade your file systems with 'fsck -c 2'"
		echo	"as soon as is feasible, because the new file system"
		echo	"code is better-tested and more performant."
		upgradefs=NO
		;;
	*)
		upgradefs=YES
		;;
esac

if [ $upgradefs = YES ]; then
	echo	""
	echo	"Upgrading the file system on ${drivename}a..."
	
	$DONTDOIT fsck -p -c 2 /dev/r${drivename}a
	if [ $? != 0 ]; then
		echo	"FATAL ERROR: FILE SYSTEM UPGRADE FAILED."
		echo	"You should probably reboot the machine, fsck your"
		echo	"disk(s), and try the upgrade procedure again."
		exit 1
	fi
	echo	"Done."
fi

echo	""
echo	"Mounting root partition on /mnt..."
$DONTDOIT mount /dev/${drivename}a /mnt
if [ $? != 0 ]; then
	echo	"FATAL ERROR: MOUNT FAILED."
	echo	"You should verify that your system is set up as you"
	echo	"described, and re-attempt the upgrade procedure."
	exit 1
fi
echo	"Done."

#<<<<<<<<<<<<<<<<<<<<<<<< update etc/fstab to ffs? >>>>>>>>>>>>>>>>>>>>>>>>
echo	""
echo -n	"Converting ufs entries in fstab to ffs..."
$DONTDOIT Convert_fstab
echo	"Done."

if [ $upgradefs = YES ]; then
	echo	""
	echo -n	"Copying new fsck binary to your hard disk..."
	if [ ! -d /mnt/sbin ]; then
		$DONTDOIT mkdir /mnt/sbin
	fi
	$DONTDOIT cp /sbin/fsck /mnt/sbin/fsck
	if [ $? != 0 ]; then
		echo	"FATAL ERROR: COPY FAILED."
		echo	"It in unclear why this error would occur.  It looks"
		echo	"like you may end up having to upgrade by hand."
		exit 1
	fi
	$DONTDOIT sync
	echo	" Done."

	echo	""
	echo    "Re-mounting root partition read-only..."
	$DONTDOIT mount -u -o ro /dev/${drivename}a /mnt
	if [ $? != 0 ]; then
		echo	"FATAL ERROR: RE-MOUNT FAILED."
		echo	"It in unclear why this error would occur.  It looks"
		echo	"like you may end up having to upgrade by hand."
		exit 1
	fi
	echo	"Done."

	echo	""
	echo	"Upgrading the rest of your file systems..."
	$DONTDOIT chroot /mnt fsck -p -c 2
	if [ $? != 0 ]; then
		echo	"FATAL ERROR: FILE SYSTEM UPGRADE(S) FAILED."
		echo	"You should probably reboot the machine, fsck your"
		echo	"file system(s), and try the upgrade procedure"
		echo	"again."
		exit 1
	fi
	echo	"Done."

	echo	""
	echo    "Re-mounting root partition read-write..."
	$DONTDOIT mount -u -o rw /dev/${drivename}a /mnt
	if [ $? != 0 ]; then
		echo	"FATAL ERROR: RE-MOUNT FAILED."
		echo	"It in unclear why this error would occur.  It looks"
		echo	"like you may end up having to upgrade by hand."
		exit 1
	fi
	echo	"Done."
fi

echo	""
echo	"Copying bootstrapping binaries and config files to the hard drive..."
$DONTDOIT pax -rwpe sbin/mount_ffs /mnt

echo	""
echo	"Mounting remaining partitions..."
$DONTDOIT chroot /mnt mount -at ffs > /dev/null 2>&1
echo	"Done."

echo    ""
echo    ""
echo	"OK!  The preliminary work of setting up your disk is now complete,"
echo	"and you can now upgrade the actual NetBSD software."
echo	""
echo	"Right now, your hard disk is mounted on /mnt.  You should consult"
echo	"the installation notes to determine how to load and install the new"
echo	"NetBSD distribution sets, and how to clean up after the upgrade"
echo	"software, when you are done."
echo	""
echo	"GOOD LUCK!"
echo	""
