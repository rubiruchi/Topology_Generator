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
 * \file point-to-point.cpp
 * \brief point-to-point link subclass.
 * \author Pierre Weiss
 * \date 2009
 */

#include "point-to-point.h"

PointToPoint::PointToPoint(const size_t &m_indice) : Link(m_indice)
{
  this->setLinkName(std::string("p2p_" + this->getIndice()));
  this->setNdcName(std::string("ndc_" + this->getLinkName()));
  this->setAllNodeContainer(std::string("all_" + this->getLinkName()));
}

PointToPoint::~PointToPoint()
{
}

std::vector<std::string> PointToPoint::GenerateHeader()
{
  std::vector<std::string> headers;
  headers.push_back("#include \"ns3/bridge-module.h\"");

  return headers;
}

std::vector<std::string> PointToPoint::GenerateLink()
{
  std::vector<std::string> generatedLink;
  generatedLink.push_back("PointToPointHelper p2p_" + this->getLinkName() + ";");
  generatedLink.push_back("p2p_" + this->getLinkName() + ".SetDeviceAttribute (\"DataRate\", StringValue (\"" + this->getDataRate() + "\"));");
  generatedLink.push_back("p2p_" + this->getLinkName() + ".SetChannelAttribute (\"Delay\", TimeValue (MilliSeconds (" + this->getLinkDelay() + ")));");

  return generatedLink;
}

std::vector<std::string> PointToPoint::GenerateNetDevice()
{
  std::vector<std::string> ndc;
  std::vector<std::string> allNodes = this->GroupAsNodeContainer();
  for(size_t i = 0; i < (size_t) allNodes.size(); i++)
  {
    ndc.push_back(allNodes.at(i));
  }
  ndc.push_back("NetDeviceContainer " + this->getNdcName() + " = p2p_" + this->getLinkName() + ".Install (" + this->getAllNodeContainer() + ");");

  return ndc;
}

std::vector<std::string> PointToPoint::GenerateTrace()
{
  std::vector<std::string> trace;

  if(this->getTrace())
  {
    trace.push_back("PointToPointHelper::EnablePcapAll (\"" + this->getLinkName() + "\");");
  }

  return trace;
}

