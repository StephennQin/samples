boost::asio::

::io_service sendheart_io;//һ�㶼��Ҫһ��server

::ip::tcp::resolver resolver(sendheart_io);//do what for resolver?
::ip::tcp::resolver::query query(string(ip), string(port))//ip/port

::ip::tcp::resolver::iterator = resolver.resolve(query);

::ssl::context ctx(::ssl::context::sslv23);

///////////construct
//������handle���صĺ��������ǳ�Ա��������async���صĶ���stream socket_�ĳ�Ա����
class temp;
{
	boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
}

::SSLAsyncClient(sendheart_io,
	ctx, iterator)
	:socket_(io_service, ctx)
	{
		socket_.lowest_layer().open(boost::asio::ip::tcp::v4());
		socket_.lowest_layer().set_option(boost::asio::ip::tcp::no_delay(true));
		socket_.set_verify_mode(boost::asio::ssl::verify_none);
		socket_.set_verify_callback(boost::bind(::verify_certificate, this, _1, _2));
		
		boost::system::error_code ec;
		boost::asio::connect(socket_.lowest_layer(), iterator, ec);
		
		socket_.async_handshake(boost:asio::ssl::stream_base::client,
			boost::bind(&::handle_handshake, this,//handle_handshake�ǳ�Ա������������ socket_.async_read_some
			boost::asio::placeholders::error));
	}
///////////////end onstruct
boost::asio::io_service * ioser = &sendheart_io;
error_code ec;
ioser->run(ec);
//////sendheart_io.run();
temp::send(data, len)
{
	boost::asio::async_write(socket_,//��async_read_some����
		boost::asio::buffer(),
		boost::bind()...)//����handle_write��ֻ�����˴����жϣ�,
}

//others
sendheart_io.reset()//���ã�
