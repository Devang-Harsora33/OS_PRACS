[<img src="https://ipinfo.io/static/ipinfo-small.svg" alt="IPinfo" width="24"/>](https://ipinfo.io/) IPinfo Python Client Library

This is the official Python client library for the IPinfo.io IP address API, allowing you to look up your own IP address, or get any of the following details for an IP:

 - [IP geolocation](https://ipinfo.io/ip-geolocation-api) (city, region, country, postal code, latitude, and longitude)
 - [ASN details](https://ipinfo.io/asn-api) (ISP or network operator, associated domain name, and type, such as business, hosting, or company)
 - [Firmographics data](https://ipinfo.io/ip-company-api) (the name and domain of the business that uses the IP address)
 - [Carrier information](https://ipinfo.io/ip-carrier-api) (the name of the mobile carrier and MNC and MCC for that carrier if the IP is used exclusively for mobile traffic)

## Getting Started

You'll need an IPinfo API access token, which you can get by signing up for a free account at [https://ipinfo.io/signup](https://ipinfo.io/signup).

The free plan is limited to 50,000 requests per month, and doesn't include some of the data fields such as IP type and company data. To enable all the data fields and additional request volumes see [https://ipinfo.io/pricing](https://ipinfo.io/pricing)

### Installation

This package works with Python 3.5 or greater. However, we only officially
support non-EOL Python versions.

```bash
pip install ipinfo
```

### Quick Start


import ipinfo
access_token = '123456789abc'
handler = ipinfo.getHandler(access_token)
ip_address = '216.239.36.21'
details = handler.getDetails(ip_address)
details.city
'Mountain View' 
details.loc
'37.3861,-122.0840'


import ipinfo
access_token = '123456789abc'
handler = ipinfo.getHandlerAsync(access_token)
ip_address = '216.239.36.21'
async def do_req():
    details = await handler.getDetails(ip_address)
    print(details.city)
    print(details.loc)

import asyncio
loop = asyncio.get_event_loop()
loop.run_until_complete(do_req())
Mountain View
37.4056,-122.0775

ip_address = '1.1.1.1'
loop.run_until_complete(do_req())
New York City
40.7143,-74.0060


import ipinfo
access_token = '123456789abc'
handler = ipinfo.getHandler(access_token)
details = handler.getDetails()
details.city
'Mountain View' 
details.loc
'37.3861,-122.0840'

import ipinfo 
handler = ipinfo.getHandler(access_token='123456789abc')

details.hostname
'any-in-2415.1e100.net'
details.country
'US'
details.country_name
'United States'

details.loc
'37.3861,-122.0840'
details.latitude
'37.3861'
details.longitude
'-122.0840'


import pprint
pprint.pprint(details.all)
{'abuse': {'address': 'US, CA, Mountain View, 1600 Amphitheatre Parkway, 94043',
           'country': 'US',
           'email': 'network-abuse@google.com',
           'name': 'Abuse',
           'network': '216.239.32.0/19',
           'phone': '+1-650-253-0000'},
 'asn': {'asn': 'AS15169',
         'domain': 'google.com',
         'name': 'Google LLC',
         'route': '216.239.36.0/24',
         'type': 'business'},
 'city': 'Mountain View',
 'company': {'domain': 'google.com', 'name': 'Google LLC', 'type': 'business'},
 'country': 'US',
 'country_name': 'United States',
 'hosting': {'host': 'google',
             'id': 'GOOGLE',
             'name': 'Google LLC',
             'network': '216.239.32.0/19'},
 'hostname': 'any-in-2415.1e100.net',
 'ip': '216.239.36.21',
 'latitude': '37.3861',
 'loc': '37.3861,-122.0840',
 'longitude': '-122.0840',
 'postal': '94035',
 'region': 'California',
 'timezone': 'America/Los_Angeles'}

import ipinfo
handler = ipinfo.getHandler(cache_options={'ttl':30, 'maxsize': 128})

import ipinfo
from ipinfo.cache.interface import CacheInterface

class MyCustomCache(CacheInterface):
    ...

handler = ipinfo.getHandler(cache=MyCustomCache())

import ipinfo
from ipinfo.handler_utils import cache_key
access_token = '123456789abc'
handler = ipinfo.getHandler(access_token)
ip_cache_key = cache_key('1.1.1.1')
ip_cache_key in handler.cache
True

handler.cache[ip_cache_key]
{'ip': '1.1.1.1', 'hostname': 'one.one.one.one', 'anycast': True, 'city': 'Miami', 'region': 'Florida', 'country': 'US', 'loc': '25.7867,-80.1800', 'org': 'AS13335 Cloudflare, Inc.', 'postal': '33132', 'timezone': 'America/New_York', 'country_name': 'United States', 'latitude': '25.7867', 'longitude': '-80.1800'}

handler.cache[ip_cache_key] = None
del handler.cache[ip_cache_key]

handler = ipinfo.getHandler(request_options={'timeout': 4})

handler = ipinfo.getHandler(headers={'user-agent': 'My Custom User-agent', 'custom_header': 'yes'})
### Internationalization

>>> import ipinfo
# Country Names: In-memory map
>>> countries = {
    "BD": "Bangladesh",
    "BE": "Belgium",
    "BF": "Burkina Faso",
    ...
}

# EU Countries: In-memory list
>>> eu_countries = [
    "IE",
    "AT",
    "LT",
    ...
]

# Country Flags: In-memory map
>>> countries_flags = {
    "AD": {"emoji": "🇦🇩", "unicode": "U+1F1E6 U+1F1E9"},
    "AE": {"emoji": "🇦🇪", "unicode": "U+1F1E6 U+1F1EA"},
    "AF": {"emoji": "🇦🇫", "unicode": "U+1F1E6 U+1F1EB"},
    ...
}

# Country Currencies: In-memory map
>>> countries_currencies = {
    "AD": {"code": "EUR", "symbol": "€"},
    "AE": {"code": "AED", "symbol": "د.إ"},
    "AF": {"code": "AFN", "symbol": "؋"},
    ...
}

# Continents: In-memory map
>>> continents = {
    "BD": {"code": "AS", "name": "Asia"},
    "BE": {"code": "EU", "name": "Europe"},
    "BF": {"code": "AF", "name": "Africa"},
    ...
}

# create handler
>>> access_token = '123456789abc'
>>> handler = ipinfo.getHandler(
    access_token,
    countries=countries,
    eu_countries=eu_countries,
    countries_flags=countries_flags,
    countries_currencies=countries_currencies,
    continents=continents
)
```
### Batch Operations

Looking up a single IP at a time can be slow. It could be done concurrently
from the client side, but IPinfo supports a batch endpoint to allow you to
group together IPs and let us handle retrieving details for them in bulk for
you.

```python
>>> import ipinfo, pprint
>>> access_token = '123456789abc'
>>> handler = ipinfo.getHandler(access_token)
>>> pprint.pprint(handler.getBatchDetails([
...   '1.1.1.1',
...   '8.8.8.8',
...   '1.2.3.4/country',
... ]))
{'1.1.1.1': {'city': '',
             'country': 'AU',
             'country_name': 'Australia',
             'hostname': 'one.one.one.one',
             'ip': '1.1.1.1',
             'latitude': '-33.4940',
             'loc': '-33.4940,143.2100',
             'longitude': '143.2100',
             'org': 'AS13335 Cloudflare, Inc.',
             'region': ''},
 '1.2.3.4/country': 'US',
 '8.8.8.8': {'city': 'Mountain View',
             'country': 'US',
             'country_name': 'United States',
             'hostname': 'dns.google',
             'ip': '8.8.8.8',
             'latitude': '37.3860',
             'loc': '37.3860,-122.0838',
             'longitude': '-122.0838',
             'org': 'AS15169 Google LLC',
             'postal': '94035',
             'region': 'California',
             'timezone': 'America/Los_Angeles'}}
```

The input size is not limited, as the interface will chunk operations for you
behind the scenes.

Please see [the official documentation](https://ipinfo.io/developers/batch) for
more information and limitations.

## Other Libraries

There are official [IPinfo client libraries](https://ipinfo.io/developers/libraries) available for many languages including PHP, Go, Java, Ruby, and many popular frameworks such as Django, Rails, and Laravel. There are also many third-party libraries and integrations available for our API.

## About IPinfo

Founded in 2013, IPinfo prides itself on being the most reliable, accurate, and in-depth source of IP address data available anywhere. We process terabytes of data to produce our custom IP geolocation, company, carrier, VPN detection, hosted domains, and IP type data sets. Our API handles over 40 billion requests a month for 100,000 businesses and developers.

[![image](https://avatars3.githubusercontent.com/u/15721521?s=128&u=7bb7dde5c4991335fb234e68a30971944abc6bf3&v=4)](https://ipinfo.io/)