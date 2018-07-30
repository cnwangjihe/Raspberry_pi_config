#!/bin/bash
if command -v systemctl >/dev/null 2>&1; then
    systemctl stop frpc
    systemctl stop RefreshpublicIP
else
    /etc/init.d/frpc stop
    /etc/init.d/RefreshpublicIP stop
fi
cp frpc /usr/bin/
mkdir /usr/share/frpc
if [ ! -f "/usr/share/frpc/frpc.ini.template" ]; then
    cp frpc.ini.template /usr/share/frpc/
fi
cp RefreshpublicIP /usr/share/frpc/
chmod 775 /usr/share/frpc/RefreshpublicIP
chmod 775 /usr/bin/frpc
chmod 777 /usr/share/frpc/frpc.ini.template
if command -v systemctl >/dev/null 2>&1; then 
    cp RefreshpublicIP.service /etc/systemd/system/
    cp frpc.service /etc/systemd/system/
    systemctl daemon-reload
    systemctl enable RefreshpublicIP
    systemctl enable frpc
    systemctl start frpc
    systemctl start RefreshpublicIP
else 
    cp RefreshpublicIP.sh /etc/init.d/RefreshpublicIP
    cp frpc.sh /etc/init.d/frpc
    chmod 775 /etc/init.d/RefreshpublicIP
    chmod 775 /etc/init.d/frpc
    /etc/init.d/frpc start
    /etc/init.d/RefreshpublicIP start
fi
echo Done!