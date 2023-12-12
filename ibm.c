// // /* CELEBP10 */                                   
// // #define _OPEN_THREADS 
// #include <libc.h>                                                          
// // #include <stdio.h>                                                              
// // #include <pthread.h>                                                            
                                                                                
// // void *thread1(void *arg)                                                        
// // {                                                                               
// //    printf("hello from the thread\n");                                           
// //    pthread_exit(NULL);                                                          
// // }                                                                               
                                                                                
// // int main()                                                                      
// // {                                                                               
// //    int            rc, stat;                                                     
// //    pthread_attr_t attr;                                                         
// //    pthread_t      thid;                                                         
                                                                                
// //    rc = pthread_attr_init(&attr);                                               
// //    if (rc == -1) {                                                              
// //       perror("error in pthread_attr_init");                                     
// //       exit(1);                                                                  
// //    }                                                                            
                                                                                
// //    rc = pthread_create(&thid, &attr, thread1, NULL);                            
// //    if (rc == -1) {                                                              
// //       perror("error in pthread_create");                                        
// //       exit(2);                                                                  
// //    }                                                                            
                                                                                
// //    rc = pthread_join(thid, (void *)&stat);                                      
// //    exit(0);                                                                     
// // }                                                                               



// /* CELEBP27 */
// #define _OPEN_THREADS
// #include <pthread.h>
// #include <stdlib.h>
// #include <stdio.h>
// void *thread(void *arg) {
//   char *ret;
//   printf("thread() entered with argument '%s'\n", arg);
//   if ((ret = (char*) malloc(20)) == NULL) {
//     perror("malloc() error");
//     exit(2);
//   }
//   strcpy(ret, "This is a test");
//   pthread_exit(ret);
// }

// int main() {
//   pthread_t thid;
//   void *ret;

//   if (pthread_create(&thid, NULL, thread, "thread 1") != 0) {
//     perror("pthread_create() error");
//     exit(1);
//   }

//   if (pthread_join(thid, &ret) != 0) {
//     perror("pthread_create() error");
//     exit(3);
//   }

//   printf("thread exited with '%s'\n", ret);
// }