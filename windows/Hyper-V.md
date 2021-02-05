### Manager Hyper-V Server Remotely ###
Server:
```powershell
# 启用远程管理
Enable-PSRemoting

# 接受远程身份认证
Enable-WSManCredSSP -Role server
```
Client:  
```
# 启用远程管理
Enable-PSRemoting

# 启用 Hyper-V 控制台和 PowerShell 管理工具功能
Enable-WindowsOptionalFeature -online -FeatureName Microsoft-Hyper-V-Tools-All

# 信任服务器
Set-Item WSMan:\localhost\Client\TrustedHosts -Value "<h-hws hidden="" class="quote-inner"> </h-hws>192.168.1.1<h-hws hidden="" class="quote-inner"> </h-hws>"

# 启用身份认证转发
Enable-WSManCredSSP -Role client -DelegateComputer "<h-hws hidden="" class="quote-inner"> </h-hws>192.168.1.1<h-hws hidden="" class="quote-inner"> </h-hws>"

# 新建凭据
cmdkey /add:192.168.1.1 /user:Administrator /pass:*********
```