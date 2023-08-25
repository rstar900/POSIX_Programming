#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>

// This function is taken from https://forums.raspberrypi.com/viewtopic.php?t=341512
void printu128(unsigned __int128 n)
{
  unsigned __int128 rem;
  
  if(n>1000000000000000000)
  {
    printu128(n/1000000000000000000);
    rem=n%1000000000000000000;
    printf("%018llu",(unsigned long long) rem); 
  }
  else
    printf("%llu",(unsigned long long) n); 
  
  return;
}


int main()
{
    // +1 as they need to contain terminating null as well
    char ipv4_addr_str[INET_ADDRSTRLEN + 1], ipv4_addr_str_re[INET_ADDRSTRLEN + 1], 
    ipv6_addr_str[INET6_ADDRSTRLEN + 1], ipv6_addr_str_re[INET6_ADDRSTRLEN + 1]; // for storing presentation form (p)

    uint32_t ipv4_addr_num; __uint128_t ipv6_addr_num; // for storing numeric form (n)

    printf("---------------------------------------------------------------------------------------------------------------\n");
    printf("Enter a valid IPv4 address here: ");
    scanf("%s", ipv4_addr_str);

    // IPv4 presentation form to numeric form conversion
    int ipv4_conversion_result = inet_pton(AF_INET, ipv4_addr_str, &ipv4_addr_num);

    if (ipv4_conversion_result == 1)
    {
        printf("Numeric form of IPv4 address %s : %u\n", ipv4_addr_str, ipv4_addr_num);

        // IPv4 numeric to presentation format
        const char* ipv4_conversion_back_result = inet_ntop(AF_INET, &ipv4_addr_num, ipv4_addr_str_re, INET_ADDRSTRLEN);
        printf("Presentation form of IPv4 numeric address %u : %s\n", ipv4_addr_num, ipv4_conversion_back_result);
    }
    else if (ipv4_conversion_result == -1)
    {
        perror("Could not convert the string to IPv4 numeric form");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Invalid IPv4 address string\n");
        exit(EXIT_FAILURE);
    }

    printf("---------------------------------------------------------------------------------------------------------------\n");
    printf("Enter a valid IPv6 address here: ");
    scanf("%s", ipv6_addr_str);

    // IPv6 presentation form to numeric form conversion
    int ipv6_conversion_result = inet_pton(AF_INET6, ipv6_addr_str, &ipv6_addr_num);

    if (ipv6_conversion_result == 1)
    {
        printf("Numeric form of IPv6 address %s : ", ipv6_addr_str);
        printu128(ipv6_addr_num);
        printf("\n");
        
        // IPv6 numeric to presentation format
        const char* ipv6_conversion_back_result = inet_ntop(AF_INET6, &ipv6_addr_num, ipv6_addr_str_re, INET6_ADDRSTRLEN);
        printf("Presentation form of IPv6 numeric address ");
        printu128(ipv6_addr_num);
        printf(" : %s\n", ipv6_conversion_back_result);
    }
    else if (ipv6_conversion_result == -1)
    {
        perror("Could not convert the string to IPv6 numeric form");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Invalid IPv6 address string\n");
        exit(EXIT_FAILURE);
    }
    
     printf("---------------------------------------------------------------------------------------------------------------\n");
    return 0;
}