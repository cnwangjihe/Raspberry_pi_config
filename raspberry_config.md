Some preparation before using Raspberry PI
==========================================

Some experience after testing for a long time.


Necessary Steps
---------------

### step 1 change the password ###
```Bash
    passwd # user:pi,oldpsw:raspberry
```

### step 2 configure the ssh ###
```Bash
    sudo nano /etc/ssh/ssh_config #set "GSSAPIAuthentication no"
    sudo nano /etc/ssh/sshd_config #set "UseDNS no"
    # then reboot
```

### step 3 set static IP ###
```Bash
    # sudo nano /etc/dhcpcd.conf
    sudo echo 'interface eth0'>>/etc/dhcpcd.conf
    sudo echo 'inform 192.168.1.101'>>/etc/dhcpcd.conf
    sudo echo 'static routers=192.168.1.118'>>/etc/dhcpcd.conf
    sudo echo 'static domain_name_servers=114.114.114.114 8.8.8.8'>>/etc/dhcpcd.conf
```

### step 4 edit hosts && change the source ###
```Bash
    # sudo nano /etc/hosts
    sudo -- sh -c -e "sudo echo '151.101.72.249 http://global-ssl.fastly.Net'>>/etc/hosts"
    sudo -- sh -c -e "sudo echo '192.30.253.112 http://github.com'>>/etc/hosts"
    # sudo nano /etc/apt/sources.list
    sudo -- sh -c -e "sudo echo 'deb http://mirrors.tuna.tsinghua.edu.cn/raspbian/raspbian/ stretch main non-free contrib'>/etc/apt/sources.list"
    sudo -- sh -c -e "sudo echo 'deb-src http://mirrors.tuna.tsinghua.edu.cn/raspbian/raspbian/ stretch main non-free contrib'>>/etc/apt/sources.list"
    sudo -- sh -c -e "sudo rm /etc/apt/sources.list.d/raspi.list"
    sudo apt-get update && sudo apt-get upgrade 
```

### step 5 install necessary packages ###
```Bash
    sudo apt-get install vim gdbserver g++ systemd git 
```

### step 6 install ntfs support ###
```Bash
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
```


Helpful Parts
-------------

### part 1 install openssl with sources code ###
```Bash
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
```

### part 2 install transmission with apt ###
```Bash
    sudo apt-get install transmission
```

### part 3 install transmission with sources code ###

Don't use this kind of ways!!!!  
It is difficult to succeed.  

```Bash
    sudo apt-get install wget libcurl4-openssl-dev libevent-dev ca-certificates libssl-dev pkg-config build-essential intltool
    git clone https://github.com/superlukia/transmission-2.92_skiphashcheck.git
    cd transmission-2.92_skiphashcheck/
    ./configure
    make && sudo make install
    # sudo nano /usr/local/share/transmission/settings.json
    # then install service
```

### part 4 install frp-server on linux ###

```Bash
    wget https://github.com/fatedier/frp/releases/download/v0.20.0/frp_0.20.0_linux_arm.tar.gz
    tar -zxvf frp_0.20.0_linux_arm.tar.gz
    cd frp_0.20.0_linux_arm
    rm frpc && rm frpc.ini
    nano ./frps.ini # ./frp/frps.ini
    # then install service
```

### part 5 git with ssh ###
```Bash
    ssh-keygen -t rsa -C "1321942045@qq.com"
    # ignore location ans passphrase.
    # Usually, the key will be stored in %HOME%/.ssh, include id_rsa ans id_rsa.pub.
    # Copy the text in id_rsa.pub to profile(github or gitlab), to add new ssh key.
```


Create Services.
------

### init.d ###

Use init.d to manage service.  
You need to change the value of `dir`,`cmd`and`user`.  
To see the template please click [here](./template_for_initd)  
```Bash
    sudo cp template_for_initd /etc/init.d/YOUR_SERVICE
    sudo chmod 775 /etc/init.d/YOUR_SERVICE
    sudo /etc/init.d/YOUR_SERVICE start # (stop|status|restart)
```
### systemd ###

Use systemd to manage service.
You need to change the value of `Description`,`User`,`Group`(*the same as User*),`ExecStart`and`ExecStop`
To see the template please click [here](./template_for_systemd)  
```Bash
    sudo cp template_for_systemd /etc/systemd/system/YOUR_SERVICE.service
    sudo systemctl daemon-reload
    sudo systemctl enable YOUR_SERVICE # start automatic
    sudo systemctl start YOUR_SERVICE # (stop|restart|disable)
```

Others
------
```Bash
    cat /sys/class/thermal/thermal_zone0/temp # check the temperature of CPU
    tar -zxvf *.tar.gz # unzip
    git -C /home/wangjihe/raspIP/ # set the location of git repositories
    top -u pi # like taskmgr
```