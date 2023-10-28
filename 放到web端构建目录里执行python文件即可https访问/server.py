import http.server
import ssl

server_address = ('', 8000)
httpd = http.server.HTTPServer(server_address, http.server.SimpleHTTPRequestHandler)

# 创建SSLContext对象
context = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
context.load_cert_chain(certfile='cert.pem', keyfile='key.pem')

# 通过SSLContext.wrap_socket()创建安全套接字连接
httpd.socket = context.wrap_socket(httpd.socket, server_side=True)

httpd.serve_forever()
