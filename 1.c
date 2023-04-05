int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine) (void *), void *arg);


const pthread_attr_t ...
		NULL ........If attr is NULL, the default attributes are used.
void *(*start_routine) (void *)
		function taht the thread should do

		
Upon successful completion, pthread_create() stores the ID of the created thread in the location referenced by thread.


The signal state of the new thread is initialised as follows:

The signal mask is inherited from the creating thread.
The set of signals pending for the new thread is empty.
If pthread_create() fails, no new thread is created and the contents of the location referenced by thread are undefined


If successful, the pthread_create() function returns zero. Otherwise, an error number is returned to indicate the error.


pthread_mutex_t fastmutex = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t recmutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;

pthread_mutex_t errchkmutex = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;

int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr);

int pthread_mutex_lock(pthread_mutex_t *mutex);

int pthread_mutex_trylock(pthread_mutex_t *mutex);

int pthread_mutex_unlock(pthread_mutex_t *mutex);

int pthread_mutex_destroy(pthread_mutex_t *mutex);  Destroy the mutex when it is no longer needed:
Note: It is important to always release the mutex after acquiring it, even in case of an error.
Also, make sure to use the same mutex variable for all threads accessing the same critical section.


Difference between processes and threads :

Both processes and threads are independent sequences of execution. The typical difference is that threads (of the same process) run in a shared memory space,
while processes run in separate memory spaces. (source: stackoverflow)

Memory race :

since the memory is shared between threads, if multiple threads try to access the same variable at the same time,
it's called a "memory race" since the "fastest" thread will modify the variable value, and then the other one will.
But the value of the first modification could have useful somewhere.

The pthread_create :

The pthread_create() function starts a new thread in the calling process.
The new thread starts execution by invoking start_routine(); arg is passed as the sole argument of start_routine().

The pthread_join :

The pthread_join() function waits for the thread specified by thread to terminate.
If that thread has already terminated, then pthread_join() returns immediately.

The pthread_mutex_init :

The pthread_mutex_init() function initializes the mutex referenced by mutex with the attributes specified by attr. If attr is NULL,
the default mutex attributes are used. When the mutex is successfully initialized, the mutex state becomes initialized and unlocked.

The pthread_mutex_destroy :
The pthread_mutex_destroy() function destroys the mutex object referenced by mutex.
The mutex object becomes uninitialized and can be reinitialized with pthread_mutex_init() if needed.

The pthread_mutex_lock :
The pthread_mutex_lock() function locks the mutex referenced by mutex.

The pthread_mutex_unlock :
The pthread_mutex_unlock() function unlocks the mutex referenced by mutex.

