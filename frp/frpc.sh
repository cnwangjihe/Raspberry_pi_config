#!/bin/sh

### BEGIN INIT INFO
# Provides:          frpc
# Required-Start:    $local_fs $network
# Required-Stop:     $local_fs
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: frpc service deamon
# Description:       frpc service daemon
### END INIT INFO

PATH=/usr/local/sbin:/usr/local/bin:/sbin:/bin:/usr/sbin:/usr/bin
DAEMON=/usr/bin/frpc
DAEMON_OPTS=-c\ /home/tmp/frpc.ini
NAME=frpc
USER=root

set -e
. /lib/lsb/init-functions

start() {
        echo -n "Starting $NAME: "
        start-stop-daemon --start \
                --user $USER \
                -m --pidfile /var/run/$NAME.pid \
                -b --exec $DAEMON -- $DAEMON_OPTS || true
        echo "$NAME."
}

stop() {
        echo -n "Stopping $NAME: "
        start-stop-daemon --stop \
                --pidfile /var/run/$NAME.pid || true
        echo "$NAME."
}

status() {
        status_of_proc -p /var/run/$NAME.pid "$DAEMON" $NAME && exit 0 || exit $?
}

case "$1" in
start)
  start
        ;;
stop)
  stop
        ;;
status)
  status
        ;;
restart)
  stop
  sleep 2
  start
        ;;
*)
        echo "Usage: $NAME {start|stop|restart|status}"
        exit 1
        ;;
esac
exit 0