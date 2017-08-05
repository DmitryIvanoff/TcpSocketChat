#include "myrunnable.h"


MyRunnable::MyRunnable(const QByteArray &da)
{
    data=QByteArray(da);
}

void MyRunnable::run()
{

     for(int i=0;i<200;++i)
     {

     }
     emit finish(data);

}

