/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 University of Strasbourg
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Pierre Weiss <3weissp@gmail.com>
 */

/**
 * \file tcp-large-transfer.h
 * \brief the tcp large transfer echo class subclass of Application.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef TCPLARGETRANSFER_H
#define TCPLARGETRANSFER_H

#include "application.h"

#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief The tcp large transfer echo subclass from Application.
 *
 *  This class represent a tcp large transfer application.
 *  It generate large tcp trafic between sender node and receiver node
 *
 *  It re-writte some methods which are called to generate the ns3 code.
 *
 *  Usage:
 *    - Create an application with tcp-large-transfert param.
 */
class TcpLargeTransfer : public Application
{
  private:
    /**
     * \brief TCP port.
     */
    size_t port;

  public:
    /**
     * \brief constructor.
     * \param m_indice number of the application on the generator applicaiton vector
     * \param m_senderNode sender node
     * \param m_receiverNode receiver node
     * \param m_startTime application start time
     * \param m_endTime application end time
     * \param port port which are sended the traffic
     */
    TcpLargeTransfer(const size_t &m_indice, const std::string &m_senderNode, const std::string &m_receiverNode, const size_t &m_startTime, const size_t &m_endTime, const size_t &port);

    /**
     * \brief destructor.
     */
    ~TcpLargeTransfer();

    /**
     * \brief generate headers code.
     * \return headers code.
     */
    virtual std::vector<std::string> GenerateHeader();

    /**
     * \brief generate application code.
     * \param netDeviceContainer net device container
     * \param numberIntoNetDevice number of the sender node into the net device container
     * \return the ns3 application code.
     */
    virtual std::vector<std::string> GenerateApplication(std::string netDeviceContainer, size_t numberIntoNetDevice);

    /**
     * \brief get port.
     * \return port.
     */
    size_t getPort();

    /**
     * \brief set port.
     * \param m_port new port.
     */
    void setPort(const size_t &m_port);
};

#endif /* TCPLARGETRANSFER_H */

