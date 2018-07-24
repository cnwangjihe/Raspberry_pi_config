usr:pi,raspberry

# step 1 change the password
    passwd 

# step 2 configure the ssh
    sudo nano /etc/ssh/ssh_config #set "GSSAPIAuthentication no"
    sudo nano /etc/ssh/sshd_config #set "UseDNS no"
    # then reboot
# step 3 set static IP
    # sudo nano /etc/dhcpcd.conf
    sudo echo 'interface eth0'>>/etc/dhcpcd.conf
    sudo echo 'inform 192.168.1.101'>>/etc/dhcpcd.conf
    sudo echo 'static routers=192.168.1.118'>>/etc/dhcpcd.conf
    sudo echo 'static domain_name_servers=114.114.114.114 8.8.8.8'>>/etc/dhcpcd.conf

# step 4 edit hosts && change the source
    # sudo nano /etc/hosts
    sudo -- sh -c -e "sudo echo '151.101.72.249 http://global-ssl.fastly.Net'>>/etc/hosts"
    sudo -- sh -c -e "sudo echo '192.30.253.112 http://github.com'>>/etc/hosts"
    # sudo nano /etc/apt/sources.list
    sudo -- sh -c -e "sudo echo 'deb http://mirrors.tuna.tsinghua.edu.cn/raspbian/raspbian/ stretch main non-free contrib'>/etc/apt/sources.list"
    sudo -- sh -c -e "sudo echo 'deb-src http://mirrors.tuna.tsinghua.edu.cn/raspbian/raspbian/ stretch main non-free contrib'>>/etc/apt/sources.list"
    sudo -- sh -c -e "sudo rm /etc/apt/sources.list.d/raspi.list"
    sudo apt-get update && sudo apt-get upgrade 

# step 5 install necessary packages
    sudo apt-get install vim gdbserver g++ systemd git 

# step 6 install ntfs support
    sudo su
    cd /usr/local/src
    rm ntfs-3g_ntfsprogs-2017.3.23.tgz
    wget https://tuxera.com/opensource/ntfs-3g_ntfsprogs-2017.3.23.tgz
    tar zxf ntfs-3g_ntfsprogs-2017.3.23.tgz
    cd ntfs-3g_ntfsprogs-2017.3.23
    ./configure && make && make install
    exit

    # sudo fdisk -l
    # sudo mount -t ntfs-3g /dev/sdb1 /mnt/usb

# part 1 install openssl with sources code
    # sudo apt-get remove openssl
    wget https://ftp.openssl.org/source/old/1.0.0/openssl-1.0.0.tar.gz
    tar -zxvf openssl-1.0.0.tar.gz
    cd openssl-1.0.0
    sudo su
    ./config  --prefix=/usr/local --openssldir=/usr/local/ssl
    make && make install_sw # (update)
    ./config shared --prefix=/usr/local --openssldir=/usr/local/ssl
    make clean
    make && make install_sw # (update)
    exit

# part 2 install transmission with apt
    sudo apt-get install transmission

# part 3 install transmission with sources code
    sudo apt-get install wget libcurl4-openssl-dev libevent-dev ca-certificates libssl-dev pkg-config build-essential intltool
    git clone https://github.com/superlukia/transmission-2.92_skiphashcheck.git
    cd transmission-2.92_skiphashcheck/
    ./configure
    make && sudo make install
    sudo nano /etc/systemd/system/transmission.service
    # ./transmission/transmission.service
    sudo systemctl daemon-reload
    sudo systemctl start transmission.service
    sudo systemctl stop transmission.service

    # sudo nano /usr/local/share/transmission/settings.json
#part

# part 4 install frp-server on linux
    wget https://github.com/fatedier/frp/releases/download/v0.20.0/frp_0.20.0_linux_arm.tar.gz
    tar -zxvf frp_0.20.0_linux_arm.tar.gz
    cd frp_0.20.0_linux_arm
    rm frpc && rm frpc.ini
    nano ./frps.ini # ./frp/frps.ini
    sudo nano /etc/systemd/system/frps.service
    # ./frp/frps.service
    sudo systemctl enable frps
    # sudo systemctl start frps
    # sudo systemctl stop frps

cat /sys/class/thermal/thermal_zone0/temp CPU温度
tar -zxvf *.tar.gz