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
 * \file tcp-large-transfer.cpp
 * \brief tcp large transfer class.
 * \author Pierre Weiss
 * \date 2009
 */

#include "tcp-large-transfer.h"
#include "generator.h"

#include "utils.h"

TcpLargeTransfer::TcpLargeTransfer(const size_t &m_indice, const std::string &m_senderNode, const std::string &m_receiverNode, const size_t &m_startTime, const size_t &m_endTime, const size_t &m_port) : Application(m_indice, m_senderNode, m_receiverNode, m_startTime, m_endTime)
{
  this->setPort(m_port);
  this->setAppName(std::string("tcp_" + this->getIndice()));
}

TcpLargeTransfer::~TcpLargeTransfer()
{
}

std::vector<std::string> TcpLargeTransfer::GenerateHeader()
{
  std::vector<std::string> headers;
  return headers;
}

std::vector<std::string> TcpLargeTransfer::GenerateApplication(std::string netDeviceContainer, size_t numberIntoNetDevice)
{
  std::vector<std::string> apps;

  apps.push_back("uint16_t port_" + this->getAppName() + " = " + utils::toString(this->port) + ";");
  apps.push_back("Address sinkLocalAddress_" + this->getAppName() + "(InetSocketAddress (Ipv4Address::GetAny (), port_" + this->getAppName() + "));");
  apps.push_back("PacketSinkHelper sinkHelper_" + this->getAppName() + " (\"ns3::TcpSocketFactory\", sinkLocalAddress_" + this->getAppName() + ");");
  apps.push_back("ApplicationContainer sinkApp_" + this->getAppName() + " = sinkHelper_" + this->getAppName() + ".Install (" + this->getReceiverNode() + ");");
  apps.push_back("sinkApp_" + this->getAppName() + ".Start (Seconds (" + this->getStartTime() + ".0));");
  apps.push_back("sinkApp_" + this->getAppName() + ".Stop (Seconds (" + this->getEndTime() + ".0));");

  apps.push_back("OnOffHelper clientHelper_" + this->getAppName() + " (\"ns3::TcpSocketFactory\", Address ());");
  apps.push_back("clientHelper_" + this->getAppName() + ".SetAttribute (\"OnTime\", RandomVariableValue (ConstantVariable (1)));");
  apps.push_back("clientHelper_" + this->getAppName() + ".SetAttribute (\"OffTime\", RandomVariableValue (ConstantVariable (0)));");

  apps.push_back("ApplicationContainer clientApps_" + this->getAppName() + ";");
  apps.push_back("AddressValue remoteAddress_" + this->getAppName() + "(InetSocketAddress (iface_" + netDeviceContainer + ".GetAddress (" + utils::toString(numberIntoNetDevice) + "), port_" + this->getAppName() + "));");
  apps.push_back("clientHelper_" + this->getAppName() + ".SetAttribute (\"Remote\", remoteAddress_" + this->getAppName() + ");");
  apps.push_back("clientApps_" + this->getAppName() + ".Add(clientHelper_" + this->getAppName() + ".Install (" + this->getSenderNode() + "));");

  apps.push_back("clientApps_" + this->getAppName() + ".Start (Seconds (" + this->getStartTime() + ".0));");
  apps.push_back("clientApps_" + this->getAppName() + ".Stop (Seconds (" + this->getEndTime() + ".0));");

  return apps;
}

size_t TcpLargeTransfer::getPort()
{
  return this->port;
}

void TcpLargeTransfer::setPort(const size_t &m_port)
{
  this->port = m_port;
}

