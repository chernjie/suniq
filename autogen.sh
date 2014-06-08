autoreconf -vfi

[ -z "$NOCONFIGURE" ] && ./configure "$@"
