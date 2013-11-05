cd libvmime

./configure --enable-platform-posix --disable-sasl \
	--disable-tls --disable-messaging-proto-pop3 \
	--disable-messaging-proto-smtp \
	--disable-messaging-proto-imap \
	--disable-messaging-proto-maildir \
	--disable-messaging-proto-sendmail \
	--disable-platform-windows

make

make install

/sbin/ldconfig

