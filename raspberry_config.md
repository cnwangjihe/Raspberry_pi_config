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
    # use publickey
    ssh-keygen -t rsa -P ***** -f raspberry -C 'for Raspberry Pi'
    cat raspberry.pub >> ~/.ssh/authorized_keys
    chmod 600 ~/.ssh/authorized_keys
    sudo nano /etc/ssh/sshd_config
    # RSAAuthentication yes
    # PubkeyAuthentication yes
    # AuthorizedKeysFile  .ssh/authorized_keys
    # PasswordAuthentication no
    # Then you should use the key "raspberry" to login, instead of password

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
### Step 6 Security ###
```Bash
    sudo ufw allow 2101
    sudo ufw enable
    sudo reboot
```

### Step 7 install ntfs support ###
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


### Step 8 Set timezone ###
```Bash
    tzselect
    sudo cp /usr/share/zoneinfo/Asia/Shanghai  /etc/localtime
    date
```

Helpful Parts
-------------

### Part 1 install openssl with sources code ###

*Not useful any more*  
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

**Attention!!!**  
Raspbian's apt- will install version 2.92,but it has a serious vulnerability.  
So, after you install it with apt, you should follow [Part 3](#part-3-install-transmission-with-sources-code)

```Bash
    sudo apt-get install transmission-daemon
```

### Part 3 install transmission with sources code ###

Don't use this kind of way(unless you use raspbian)  
It is difficult to succeed.  

```Bash
    sudo apt-get install build-essential automake autoconf libtool pkg-config intltool libcurl4-openssl-dev libglib2.0-dev libevent-dev libminiupnpc-dev libgtk-3-dev libappindicator3-dev ca-certificates libcurl4-openssl-dev libssl-dev pkg-config build-essential checkinstall
    wget https://raw.githubusercontent.com/transmission/transmission-releases/master/transmission-2.94.tar.xz # Don't use the wrong url
    tar -xf transmission-2.94.tar.xz
    cd transmission-2.94
    ./configure --prefix=/usr && make
    sudo make install
    sudo nano /etc/systemd/system/transmission-daemon.service
    {
        [Unit]
        Description=Transmission BitTorrent Daemon
        After=network.target

        [Service]
        User=debian-transmission
        Type=simple
        ExecStart=/usr/bin/transmission-daemon -f --log-error
        ExecStop=/bin/kill -s STOP $MAINPID
        ExecReload=/bin/kill -s HUP $MAINPID
        Restart=always
        RestartSec=10

        [Install]
        WantedBy=multi-user.target
    }
    sudo systemctl daemon-reload
    sudo systemctl enable transmission-daemon.service
    sudo systemctl start transmission-daemon.service
```
By the way, the .config folder is at ```/var/lib/transmission-daemon```, or you can use ```sudo cat /etc/passwd``` to check the main folder of user debian-transmission(or transmission).  
And the settings.json is at ```/etc/transmission-daemon```

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

#### The first way:  ####
Use acme.sh to set up *(take nginx for example)*  

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

Deploying Diffie-Hellman for TLS  

```Bash
    cd /etc/nginx/ssl
    openssl dhparam -out dhparams.pem 2048
    # Then configure nginx
```  

more information:  
[Let's encrypt with DNS in TXT](https://blog.csdn.net/u012291393/article/details/78768547)  
[Transmission web interface with SSL](https://moeclub.org/2017/07/11/318)  
[SSLlabs](https://www.ssllabs.com/)  
[Deploying Diffie-Hellman for TLS](https://weakdh.org/sysadmin.html)  

### Part 7 nginx ###

Install:  
```sudo apt-get install nginx nginx-extras```  

The template for /etc/nginx/conf.d/xxx.conf  

```
server
{
        # Use ssl only
        listen 443;
        ssl on;
        server_name wangjihe.tk;
        ssl_certificate /etc/nginx/ssl/wangjihe.tk/fullchain.pem;
        ssl_certificate_key /etc/nginx/ssl/wangjihe.tk/privkey.pem;
        ssl_trusted_certificate /etc/nginx/ssl/wangjihe.tk/ca.pem;
        
        # Set HSTS
        add_header Strict-Transport-Security "max-age=31536000; includeSubDomains" always;

        # Deploying Diffie-Hellman
        ssl_ciphers 'ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-AES256-GCM-SHA384:DHE-RSA-AES128-GCM-SHA256:DHE-DSS-AES128-GCM-SHA256:kEDH+AESGCM:ECDHE-RSA-AES128-SHA256:ECDHE-ECDSA-AES128-SHA256:ECDHE-RSA-AES128-SHA:ECDHE-ECDSA-AES128-SHA:ECDHE-RSA-AES256-SHA384:ECDHE-ECDSA-AES256-SHA384:ECDHE-RSA-AES256-SHA:ECDHE-ECDSA-AES256-SHA:DHE-RSA-AES128-SHA256:DHE-RSA-AES128-SHA:DHE-DSS-AES128-SHA256:DHE-RSA-AES256-SHA256:DHE-DSS-AES256-SHA:DHE-RSA-AES256-SHA:AES128-GCM-SHA256:AES256-GCM-SHA384:AES128-SHA256:AES256-SHA256:AES128-SHA:AES256-SHA:AES:CAMELLIA:DES-CBC3-SHA:!aNULL:!eNULL:!EXPORT:!DES:!RC4:!MD5:!PSK:!aECDH:!EDH-DSS-DES-CBC3-SHA:!EDH-RSA-DES-CBC3-SHA:!KRB5-DES-CBC3-SHA';
        ssl_prefer_server_ciphers on;
        ssl_dhparam /etc/nginx/ssl/dhparams.pem;

        # Hide server information
        server_tokens off;
        more_clear_headers Server;

        # Prevent others using these web pages in iframe
        add_header X-Frame-Options SAMEORIGIN; # or you can use DENY
        
        root /var/www/wangjihe;

        location ~* /
        {
                # auth may not necessary (optional)
                auth_basic "\n";
                auth_basic_user_file /etc/nginx/password;

                # For proxy (optional)
                proxy_pass http://127.0.0.1:10101;
                
                # For file server, please change the root
                autoindex on;
                autoindex_exact_size off;
                autoindex_localtime on;
        }
        error_page 497  https://$host$uri?$args;
        
        # For php server (optional)
        index index.php;
        location / {
                # First attempt to serve request as file, then
                # as directory, then fall back to displaying a 404.
                try_files $uri $uri/ =404;
        }
        location ~ \.php$ {
                include snippets/fastcgi-php.conf;

                # With php7.0-cgi alone:
                # fastcgi_pass 127.0.0.1:9000;
                # With php7.0-fpm:
                fastcgi_pass unix:/run/php/php7.0-fpm.sock;
        }
}
```  

And if you set the option "auth_basic", remember to change the password  

```Bash
    echo -n 'USERNAME:' >>/etc/nginx/password
    openssl passwd PASSWORD >>/etc/nginx/password
    # better not longer than 8
```

### Part 8 php ###

Install php-fpm only.(without mysql)  
```sudo apt-get install php7.0-fpm```

Configure php.ini *(remember to use Ctrl+w to search)*  
```Bash
    sudo nano /etc/php/7.0/fpm/php.ini
    {
        session.use_strict_mode = 1
        session.cookie_secure = 1
        ; use https to transport cookies
        session.cookie_lifetime = 900
        ; 15 minutes
    }
```  

### Part 9 squid ###

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

### Part 10 samba ###

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

### Part 11 DDNS ###

The project of NewFuture, [DDNS](https://github.com/NewFuture/DDNS) Support Cloudflare, Dnspod, Dns.com ...  
Use cron to run automatically:  
```Bash
    crontab -e
    {
        */5 * * * * /usr/bin/python "/home/pi/DDNS/run.py" -c "/home/pi/DDNS/cloudflare.json" >> "/home/pi/DDNS/cloudflare.log"
    }
```

### Part 12 Setup ups ###

If you have an ups of APC, you can install apcupsd to receive a power down signal.  

To see whether your ups is recognized:  
```Bash
    lsusb
    udevadm info --attribute-walk --name=/dev/usb/hiddev0 | egrep 'manufacturer|product|serial'
```  
To install apcupsd:  
```Bash
    sudo apt-get install apcupsd apcupsd-doc
    sudo nano /etc/apcupsd/apcupsd.conf
```  
Which values you need to change(example for BK650-CH):  
  ```UPSNAME BK650-CH```:Any name you like, It's not important.  
  ```UPSCABLE usb```:The cable your ups uses.  
  ```UPSTYPE usb```:The type of your ups.  
  ```DEVICE ```:If you use usb type, you can leave it empty.  
  ```BATTERYLEVEL 15```:If during a power failure, the remaining battery percentage that apcupsd will initiate a system shutdown.  
  ```MINUTES 20```:After X minutes without wall power, system will be shutdown.  
  ```TIMEOUT 0```:After X seconds without wall power, system will be shutdown.(0 means disable this option)  
  ```KILLDELAY 0```:Shutdown will be delayed for X seconds.(0 means disable this option)  

Then:  
```Bash
    sudo -- sh -c -e "sudo echo 'ISCONFIGURED=yes'>/etc/default/apcupsd"
    sudo systemctl enable apcupsd
    sudo systemctl start apcupsd
```

More information:  
[http://www.apcupsd.com/manual/manual.html](http://www.apcupsd.com/manual/manual.html)  
[https://wiki.archlinux.org/index.php/APC_UPS](https://wiki.archlinux.org/index.php/APC_UPS)  
*You can find the way to change the script that apcupsd will execute*  
[https://wiki.debian.org/apcupsd](https://wiki.debian.org/apcupsd)  

### Part 13 install crypto++ ###

Use source code to install.  

```Bash
    cd /tmp
    mkdir cryptopp7 && cd cryptopp7
    wget https://www.cryptopp.com/cryptopp700.zip
    unzip cryptopp700.zip
    export CXXFLAGS="-DNDEBUG -g2 -O3 -std=c++11"
    make && make test
    sudo make install
    cd ..
    rm -rf cryptopp7
    # g++ -std=c++11 file_name.cpp -o file_name -Wall -Wextra -Wparentheses -O2 -DNDEBUG -I/usr/include/cryptopp -lcryptopp -lpthread
```  
[Install](https://github.com/weidai11/cryptopp/blob/master/Install.txt)  
[Usage](https://www.cryptopp.com/docs/ref/)  

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
### Compression ###

```Bash
    cat /sys/class/thermal/thermal_zone0/temp # check the temperature of CPU
    tar -zxvf *.tar.gz # unzip
    tar -xf *.tar.xz # unzip
    git -C /home/wangjihe/raspIP/ # set the location of git repositories
    top -u pi # like taskmgr
    tar -cvf /tmp/etc.tar /etc # Only bale, not compress
    tar -czvf /tmp/etc.tar.gz /etc # compress with gzip
    tar -cjvf /tmp/etc.tar.bz2 /etc # compress with bzip2
    # Sublime text 3 ,Preferences -> Settings-Syntax Specific -> "default_line_endings":"unix"
```
  
### Network "top" ###

Both ```iftop``` and ```nethogs``` are useful.  
You can simply use ```apt-get``` to install them.  
