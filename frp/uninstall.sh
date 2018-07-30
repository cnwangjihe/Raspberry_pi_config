#!/bin/bash
cd /etc/systemd/system
systemctl disable frpc
systemctl disable RefreshpublicIP
systemctl stop frpc
systemctl stop RefreshpublicIP
rm RefreshpublicIP.service frpc.service
cd /usr/share
rm -rf frpc
rm ../bin/frpc
systemctl daemon-reload
