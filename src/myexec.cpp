#include "derived.h"
#include <vector>
#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Starting the APP\n");
    DerivedCpp obj = DerivedCpp("DerivedExample");
    uint8_t resRun, resStop;

    std::vector<uint8_t> args {42, 43, 44, 45};
    
    printf("Call Run\n");
    resRun = obj.Run(args);
    printf("Run Got: %d\n", resRun);
    
    usleep(50000);
    
    printf("Call Stop\n");
    resStop = obj.Stop(args);
    printf("Stop Got: %d\n", resStop);

    usleep(50000);
    return 0;
}