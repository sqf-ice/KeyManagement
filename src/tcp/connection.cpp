//
// Created by Hanzeil on 16-9-4.
//
// Copyright (c) 2016 航天二院爱威公司. All rights reserved.
//
// Author Hanzeil.
//

#include "connection.h"
#include <utility>
#include <vector>
#include "connection_manager.h"

namespace http {
    namespace server {

        connection::connection(boost::asio::io_service &io_service,
                               connection_manager &manager, RequestHandler &handler)
                : socket_(io_service),
                  connection_manager_(manager),
                  request_handler_(handler) {
        }

        void connection::start() {
            do_read();
        }

        void connection::stop() {
            socket_.close();
        }

        void connection::Reset() {
            request_parser_.reset();
            request_.Reset();
            reply_.Reset();
        }

        void connection::do_read() {
            auto self(shared_from_this());
            socket_.async_read_some(boost::asio::buffer(buffer_),
                                    [this, self](boost::system::error_code ec, std::size_t bytes_transferred) {
                                        if (!ec) {
                                            std::cout << "bytes_transferred: " << bytes_transferred << std::endl;
                                            RequestParser::result_type result;
                                            std::tie(result, std::ignore) = request_parser_.parse(
                                                    request_, buffer_.data(), buffer_.data() + bytes_transferred);
                                            self->Reset();
                                            if (result == RequestParser::good) {
                                                request_handler_.handle_request(request_, reply_);
                                            }
                                            do_write();
                                        }
                                        else if (ec != boost::asio::error::operation_aborted) {
                                            connection_manager_.stop(shared_from_this());
                                        }
                                    });
        }

        void connection::do_write() {
            auto self(shared_from_this());
            boost::asio::async_write(socket_, reply_.to_buffers(),
                                     [this, self](boost::system::error_code ec, std::size_t len) {
                                         if (!ec) {
                                             do_read();
                                             /*
                                             // Initiate graceful connection closure.
                                             boost::system::error_code ignored_ec;
                                             socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
                                                              ignored_ec);
                                                              */
                                         }

                                         /*
                                         if (ec != boost::asio::error::operation_aborted) {
                                             connection_manager_.stop(shared_from_this());
                                         }
                                          */
                                     });
        }

    } // namespace server
} // namespace http