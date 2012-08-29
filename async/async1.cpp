#include <iostream>
#include <thread>
#include <future>

using namespace std;

int main()
{

    // Create future for running lambda asynchronously
    // Note: launch::async is specified to force creating a separate thread
    auto fut = async( std::launch::async, []()->int {
                            // simulate long running task
                            this_thread::sleep_for( chrono::seconds(5) );
                            // return value
                            return 32;
                        } );

    while ( true )
    {
        // Do we have future results?
        if ( fut.wait_for( chrono::milliseconds(0) ) == future_status::ready )
        {
            // We have results from the other thread
            cout << "\nValue returned from future: " << fut.get() << endl;
            break;
        }

        // Give our timeslot for other processes
        this_thread::yield();

        // Sleep 100ms
        this_thread::sleep_for( chrono::milliseconds(100) );

        // Output something to indicate that we are alive :)
        cout << ".";
    }

    return 0;
}
