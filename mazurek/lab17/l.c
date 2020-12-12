/*****************************************************************************
* This example shows how to use PAPI_add_event, PAPI_start, PAPI_read,       *
*  PAPI_stop and PAPI_remove_event.                                          *
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <papi.h> /* This needs to be included every time you use PAPI */

#define NUM_EVENTS 2
#define ERROR_RETURN(retval)                                                    \
    {                                                                           \
        fprintf(stderr, "Error %d %s:line %d: \n", retval, __FILE__, __LINE__); \
        exit(retval);                                                           \
    }

long long data[200];
int main()
{
    for (int i = 0; i < 200; i++)
    {
        int EventSet = PAPI_NULL;

        /*must be initialized to PAPI_NULL before calling PAPI_create_event*/
        long long values[NUM_EVENTS];
        /*This is where we store the values we read from the eventset */

        /* We use number to keep track of the number of events in the EventSet */
        int retval, number;
        char errstring[PAPI_MAX_STR_LEN];

        /*************************************************************************** 
         *  This part initializes the library and compares the version number of the*
         * header file, to the version of the library, if these don't match then it *
         * is likely that PAPI won't work correctly.If there is an error, retval    *
         * keeps track of the version number.                                       *
         ***************************************************************************/

        if ((retval = PAPI_library_init(PAPI_VER_CURRENT)) != PAPI_VER_CURRENT)
            ERROR_RETURN(retval);

        /* Creating the eventset */
        if ((retval = PAPI_create_eventset(&EventSet)) != PAPI_OK)
            ERROR_RETURN(retval);

        /* Add Total Instructions Executed to the EventSet */
        if ((retval = PAPI_add_event(EventSet, PAPI_TOT_INS)) != PAPI_OK)
            ERROR_RETURN(retval);

        /* Add Total Cycles event to the EventSet */
        if ((retval = PAPI_add_event(EventSet, PAPI_TOT_CYC)) != PAPI_OK)
            ERROR_RETURN(retval);

        /* get the number of events in the event set */
        number = 0;
        if ((retval = PAPI_list_events(EventSet, NULL, &number)) != PAPI_OK)
            ERROR_RETURN(retval);

        /* Start counting */

        if ((retval = PAPI_start(EventSet)) != PAPI_OK)
            ERROR_RETURN(retval);

        /* you can replace your code here */
        unsigned long long sum = 0;
        for (int j = 1; j <= 50000; j++)
            for (int k = 1; k <= 4000; k++)
                sum += j * k - (sum / k) + 3;

        /* read the counter values and store them in the values array */
        if ((retval = PAPI_read(EventSet, values)) != PAPI_OK)
            ERROR_RETURN(retval);

        data[i] = values[0];

        if ((retval = PAPI_stop(EventSet, values)) != PAPI_OK)
            ERROR_RETURN(retval);

        /* free the resources used by PAPI */
        PAPI_shutdown();
    }

    for (int i = 0; i < 100; ++i)
    {
        printf("%i\t\t%lld\n", i + 1, data[i]);
        fflush(stdout);
    }

    exit(0);
}
