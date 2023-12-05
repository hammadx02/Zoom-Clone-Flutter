#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <bitset>

using namespace std;

// Structure to represent a routing entry in the routing table
struct RoutingEntry {
  string destination;
  string subnetMask;
  string nextHop;
  string interface;
};

// Function to convert CIDR notation to subnet mask
string cidrToSubnetMask(int cidr) {
  if (cidr < 0 || cidr > 32) {
    throw invalid_argument("Invalid CIDR notation.");
  }

  bitset
 
bits(0xFFFFFFFF);
  bits <<= (32 - cidr);

  stringstream ss;
  for (size_t i = 0; i < 4; ++i) {
    ss << static_cast<int>((bits >> (8 * i)).to_ulong());
    if (i < 3) {
      ss << ".";
    }
  }

  return ss.str();
}

// Function to check if an IP address matches a routing entry using CIDR notation

bool
 
matchCIDR(const
 
string& ipAddress, const
 
string& destination, const
 
string& subnetMask)
 
{
  size_t cidrPos = subnetMask.find('/');
  if (cidrPos != string::npos) {
    int cidr = stoi(subnetMask.substr(cidrPos + 1));
    string subnet = subnetMask.substr(0, cidrPos);

    string subnetMaskCalculated = cidrToSubnetMask(cidr);

    size_t subnetSize = min(subnet.size(), subnetMaskCalculated.size());
    return ipAddress.compare(0, subnetSize, subnet) == 0 &&
           subnetMask.compare(0, subnetSize, subnetMaskCalculated) == 0;
  } else {
    // If no CIDR notation, check exact match

    
return ipAddress == destination;
  }
}

int
 
main()
 
{
  // Create a routing table

  
vector<RoutingEntry> routingTable;

  // Add a routing entry for the default route
  RoutingEntry defaultRouteEntry;
  defaultRouteEntry.destination = "0.0.0.0";
  defaultRouteEntry.subnetMask = "0.0.0.0";
  defaultRouteEntry.nextHop = "192.168.1.1";
  defaultRouteEntry.interface = "eth0";

  routingTable.push_back(defaultRouteEntry);

  // Add a routing entry for a specific network
  RoutingEntry specificNetworkEntry;
  specificNetworkEntry.destination = "192.168.1.0";
  specificNetworkEntry.subnetMask = "255.255.255.0";
  specificNetworkEntry.nextHop = "192.168.1.1";
  specificNetworkEntry.interface = "eth0";

  routingTable.push_back(specificNetworkEntry);

  // Get the IP address to match against the routing table

  
string ipAddress = "192.168.1.100";

  // Iterate over the routing table and try to match the IP address

  
for (const
 
auto& routingEntry : routingTable) {
    if (matchCIDR(ipAddress, routingEntry.destination, routingEntry.subnetMask)) {
      // The IP address matches a routing entry

      
cout << "The IP address " << ipAddress << " matches the routing entry " << routingEntry.destination << endl;
      break;
    }
  }

  return
 
0;
}