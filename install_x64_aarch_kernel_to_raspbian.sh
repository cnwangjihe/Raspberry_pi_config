        sudo su
# Step0: Mount SD card
        mount /dev/sdb1 /mnt/boot
        mount /dev/sdb2 /mnt/root
# Step1: Cross compile your kernel with 64bit.
        make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- bcmrpi3_defconfig
        make -j 6 ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu-

# Step2: Copy File into sdcard boot dir.
        cp arch/arm64/boot/dts/broadcom/bcm2837-rpi-3-b.dtb  /mnt/boot/
        cp arch/arm64/boot/dts/overlays/*.dtbo /mnt/boot/overlays/
        cp arch/arm64/boot/Image /mnt/boot/kernel8.img

# Step3: Copy modules into sdcard root dir.
        make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu-  INSTALL_MOD_PATH=/mnt/root/ modules_install

# Step4: Mention these two line into "config.txt". without it won't boot up.
        echo "device_tree=bcm2837-rpi-3-b.dtb" >> /mnt/boot/config.txt
        echo "kernel=kernel8.img" >> /mnt/boot/config.txt

# Step5: Umount SD card and enjoy your raspbian with 64bit kernel
        umount /dev/sdb1
        umount /dev/sdb2