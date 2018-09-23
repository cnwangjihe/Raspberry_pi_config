Some preparation before using Raspberry PI
==========================================

Some experience after testing for a long time.


Necessary Steps
---------------

### Step 1 change the password ###
```Bash
    passwd # user:pi,oldpsw:raspberry
```

### Step 2 configure the ssh ###
```Bash
    sudo nano /etc/ssh/ssh_config #set "GSSAPIAuthentication no"
    sudo nano /etc/ssh/sshd_config #set "UseDNS no && Port 2101"
    # then reboot
```

### Step 3 set static IP ###
```Bash
    # sudo nano /etc/dhcpcd.conf
    sudo echo 'interface eth0'>>/etc/dhcpcd.conf
    sudo echo 'inform 192.168.31.101'>>/etc/dhcpcd.conf
    sudo echo 'static routers=192.168.31.1'>>/etc/dhcpcd.conf
    sudo echo 'static domain_name_servers=114.114.114.114 8.8.8.8'>>/etc/dhcpcd.conf
```

### Step 4 edit hosts && change the source ###
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

### Step 5 install necessary packages ###
```Bash
    sudo apt-get install vim gdbserver g++ systemd git ufw
```

### Step 6 install ntfs support ###
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

### Step 7 Security ###
```Bash
    sudo ufw allow 2101
    sudo ufw enable
    sudo reboot
```

### Step 8 Set timezone ###
```Bash
    tzselect
    sudo cp /usr/share/zoneinfo/Asia/Shanghai  /etc/localtime
    date
```

Helpful Parts
-------------

### Part 1 install openssl with sources code ###
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

### Part 2 install transmission with apt ###
```Bash
    sudo apt-get install transmission-daemon
```

### Part 3 install transmission with sources code ###

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

### Part 4 install frp-server on linux ###

```Bash
    wget https://github.com/fatedier/frp/releases/download/v0.21.0/frp_0.21.0_linux_arm.tar.gz
    tar -zxvf frp_0.21.0_linux_arm.tar.gz
    cd frp_0.21.0_linux_arm
    sudo cp ./frps /usr/bin
    sudo mkdir /etc/frps
    sudo cp ./frps.ini /etc/frps
    cd ..
    rm -rf frp_0.21.0_linux_arm
    rm frp_0.21.0_linux_arm.tar.gz
    cd /etc/frps
    # then install service
```

### Part 5 git with ssh ###

```Bash
    ssh-keygen -t rsa -C "1321942045@qq.com"
    # ignore location ans passphrase.
    # Usually, the key will be stored in %HOME%/.ssh, include id_rsa ans id_rsa.pub.
    # Copy the text in id_rsa.pub to profile(github or gitlab), to add new ssh key.
```

### Part 6 use ssl to connect web interface ###

use [let's encrypt](https://letsencrypt.org/)

####The first way:  ####
Use acme.sh to set up  

```Bash
    curl https://get.acme.sh | sh
    alias acme.sh=~/.acme.sh/acme.sh
    # sudo -- sh -c -e "echo '45 0 * * * sudo \"/home/pi/.acme.sh\"/acme.sh --cron --home \"/home/pi/.acme.sh\" > /dev/null' >> /var/spool/cron/crontabs/pi"
    sudo mkdir /etc/nginx/ssl 
    sudo chmod -R 777 /etc/nginx/ssl
    export DP_Id="XXXXXX"
    export DP_Key="XXXXXXXXXXXXX"
    # use the api of DNSpod
    DOMAIN=wangjihe.tk
    mkdir /etc/nginx/ssl/$DOMAIN
    acme.sh --issue --dns dns_dp -d $DOMAIN
    # if you use cloudflare
    # CF_Email=XXX@XX.XX
    # CF_Key=XXXXXXXXX
    # acme.sh --issue --dns dns_cf -d $DOMAIN
    acme.sh --install-cert -d $DOMAIN \
    --cert-file      /etc/nginx/ssl/$DOMAIN/ca.pem  \
    --key-file       /etc/nginx/ssl/$DOMAIN/privkey.pem  \
    --fullchain-file /etc/nginx/ssl/$DOMAIN/fullchain.pem \
    --ca-file      /etc/nginx/ssl/$DOMAIN/chain.pem  \
    --reloadcmd     "sudo service nginx force-reload"
    # acme.sh --renew -d example.com --force
    # force refresh
    acme.sh --upgrade --auto-upgrade # update automatically
```
then deploy nginx  


#### The second way:  ####
use certbot *(Not recommended)*  

```Bash
    DOMAIN=wangjihe.tk
    # if you use apache, replace -nginx with -apache
    sudo certbot --manual --preferred-challenges dns certonly
    sudo mkdir /etc/nginx/ssl 
    sudo chmod -R 777 /etc/nginx/ssl
    mkdir /etc/nginx/ssl/$DOMAIN
    cp /etc/letsencrypt/live/$DOMAIN/fullchain.pem /etc/nginx/$DOMAIN/fullchain.pem 
    cp /etc/letsencrypt/live/$DOMAIN/privkey.pem /etc/nginx/$DOMAIN/privkey.pem 
    cp /etc/letsencrypt/live/$DOMAIN/chain.pem /etc/nginx/$DOMAIN/chain.pem 
    # use DNS to get cert(it won't update automatically,and you need to change xxx.conf by yourself)
```
Or  
```Bash
    sudo apt-get install python-certbot-nginx
    sudo sudo certbot --authenticator webroot --installer nginx # use exist web server
```  


#### Template of /etc/nginx/conf.d/xxx.conf  ####

```
server
{
        listen 443;
        listen 80;
        ssl on;
        server_name wangjihe.tk;
        ssl_certificate /etc/nginx/ssl/wangjihe.tk/fullchain.pem;
        ssl_certificate_key /etc/letsencrypt/live/wangjihe.tk/privkey.pem;
        ssl_trusted_certificate /etc/letsencrypt/live/wangjihe.tk/chain.pem;
        location ~* /
        {
                auth_basic "\n";
                auth_basic_user_file /etc/nginx/password; 
                proxy_pass http://127.0.0.1:10101; 
        }
        error_page 497  https://$host$uri?$args;

}
```  

And remenber to change the password  

```Bash
    echo -n 'USERNAME:' >>/etc/nginx/password
    openssl passwd PASSWORD >>/etc/nginx/password
    # better not longer than 8
```

more information:  
[Let's encrypt with DNS in TXT](https://blog.csdn.net/u012291393/article/details/78768547)  
[Transmission web interface with SSL](https://moeclub.org/2017/07/11/318)  

### Part 7 squid ###

squid is a powerful proxy.  

```Bash
    sudo apt-get install squid
    sudo nano /etc/squid/squid.conf
```

Add these to the front of squid.conf  

```
    http_port 7111
    http_access allow all
    acl localnet src 192.168.1.0/24
```

### Part 8 samba ###  

```Bash
    sudo apt-get install samba samba-common-bin
    sudo pdbedit –a pi
    sudo nano /etc/samba/smb.conf
    {
        [HDD0]
            comment=HDD0
            path=/mnt/HDD0
            browseable=yes
            writable=yes
            available=yes
            admin users=pi
            valid users=pi
            write list=pi
            public=no
    }
    sudo systemctl restart smbd
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
You need to change the value of `Description`,`User`,`Group`(*the same as User*),`WorkingDirectory`,`ExecStart`and`ExecStop`.
*Notice:The space in WorkingDirectory should be replaced by \x20*
To see the template please click [here](./template_for_systemd)  
```Bash
    sudo cp template_for_systemd /etc/systemd/system/YOUR_SERVICE.service
    sudo systemctl daemon-reload
    sudo systemctl enable YOUR_SERVICE # start automatic
    sudo systemctl start YOUR_SERVICE # (stop|restart|disable)
```
### WinSW ###

Use WinSW to install service on Windows.  
Please install .Net 4.  
[Here](https://github.com/kohsuke/winsw) has detailed information.  
An [example](./WinSW.xml) for frpc.  
*Notice: if you see the error"WMI Operation failure: AccessDenied",Please check if you have used cipher to encrypt your files.*

Others
------
```Bash
    cat /sys/class/thermal/thermal_zone0/temp # check the temperature of CPU
    tar -zxvf *.tar.gz # unzip
    git -C /home/wangjihe/raspIP/ # set the location of git repositories
    top -u pi # like taskmgr
    tar -cvf /tmp/etc.tar /etc # Only bale, not compress
    tar -czvf /tmp/etc.tar.gz /etc # compress with gzip
    tar -cjvf /tmp/etc.tar.bz2 /etc # compress with bzip2
    # Sublime text 3 ,Preferences -> Settings-Syntax Specific -> "default_line_endings":"unix"
```
