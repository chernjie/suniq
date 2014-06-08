#!/bin/sh

autoreconf -vfi

[ -z "$NOCONFIGURE" ] && ./configure "$@"
