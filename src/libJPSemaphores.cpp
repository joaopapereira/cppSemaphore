/**
 *  Copyright 2012 Joao Pereira<joaopapereira@gmail.com>
 *
 *
 *  This file is part of libJPSemaphores.
 *
 *  libJPSemaphores is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  libJPSemaphores is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "libJPSemaphores.hpp"

#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <iostream>
#include <libJPLogger.h>
#include <string.h>
#include <stdlib.h>

#define _SEMBASEMASK 0666
#define _SEMDEFID 1234
#define _SEMDEFVAL 0
#define _SEMDEFMAX 1

int JPSemaphoreId::semIdentifier = 1000;
int JPSemaphoreId::getnextId(){
	return semIdentifier++;
}


static std::string modName("SEM");
JPSemaphore::JPSemaphore( int semId , int sValue )
{
//	sem_init( &sem , pShared , sValue );
	OneInstanceLogger::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"JPSemaphore(%d,%d)",semId,sValue);
	this->semId = semId;
	actualValue = sValue;
	maxValue = sValue;
	//char name[50];
	char * semName = (char*)malloc( sizeof(char) * 50);
	sprintf(semName,"M%d_%d",semId,getpid());

	sem = sem_open(semName, O_CREAT , S_IRUSR|S_IWUSR, 0);


	//int res = semget ((key_t) semId, _SEMDEFNUM + 1, _SEMBASEMASK | IPC_CREAT | IPC_EXCL);

	//if( res != -1 )
	if( SEM_FAILED != sem )
		initSem();
	else{
		OneInstanceLogger::instance()->log(modName,M_LOG_LOW,M_LOG_ERR,"EJPSemaphore(%d,%d):this=%p:errno",semId,actualValue,this,errno);
	}
	free( semName );
	OneInstanceLogger::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"EJPSemaphore(%d,%d):this=%p",semId,actualValue,this);
}

JPSemaphore::JPSemaphore()
{
	OneInstanceLogger::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"JPSemaphore()");
//	sem_init( &sem , 0 , 1 );
	semId = JPSemaphoreId::getnextId();
	OneInstanceLogger::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"semId(%d)",semId);
	actualValue = _SEMDEFVAL;
	maxValue = _SEMDEFMAX;
	OneInstanceLogger::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"actualValue(%d), maxValue(%d)", actualValue,maxValue);
	//char * semName = (char*)malloc( sizeof(char) * 50);
	char semName[50];
	//char semName[100];
	OneInstanceLogger::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"done alloc");
	sprintf(semName,"M%d_%d",semId,getpid());
	OneInstanceLogger::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"semname(%s)",semName);
	sem = sem_open(semName, O_CREAT , S_IRUSR|S_IWUSR, 0);
	//if( res != -1 )
	if( SEM_FAILED != sem )
		initSem();
	//free( semName );
	OneInstanceLogger::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"EJPSemaphore(%d,%d):this=%p",semId,actualValue,this);
}

JPSemaphore::~JPSemaphore()
{
	//int res = (semctl (semId, 0, IPC_RMID, NULL));
	int res = sem_close(sem);
	/*if( res == 0 )
		initSem();*/
//	sem_destroy( &sem );
}


int JPSemaphore::down(){
	OneInstanceLogger::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"down():this=%p,id[%d]",this,semId);
	return int_down();
}
int JPSemaphore::int_down(){
	OneInstanceLogger::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"int_down():this=%p,id[%d]",this,semId);
//	struct sembuf down = { semId, -1, SEM_UNDO };
	int stat,actVal;

//	down.sem_num = (unsigned short) semId;
//	down.sem_op = -1;
//	down.sem_flg = SEM_UNDO;
	/*do {
		stat = semop (semId, &down, 1);
		OneInstanceLogger::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"Edown():this=%p:statsemop=%d:errno=%d:msg=%s",this,stat,errno, strerror(errno) );
	}while((stat == -1) && (errno == EINTR));*/
	stat =  sem_wait( sem );
	if( 0 != stat ){
		OneInstanceLogger::instance()->log(modName,M_LOG_LOW,M_LOG_ERR,"Edown():this=%p:statsemop=%d:errno=%d:msg=%s",this,stat,errno, strerror(errno) );
		return -1;
	}
	actualValue--;
	stat = sem_getvalue(sem , &actVal );
	OneInstanceLogger::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"Eint_down():this=%p:val=%d",this,actVal);

	return stat;
}

int JPSemaphore::up(){
	OneInstanceLogger::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"up():this=%p,id[%d]",this,semId);
	return int_up();
}
int JPSemaphore::int_up(){
	OneInstanceLogger::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"int_up():this=%p,id[%d]",this,semId);
//	struct sembuf up = { semId, 1, 0 };
	int stat,actVal;

//	up.sem_num = (unsigned short) semId;
//	up.sem_op = -1;
//	up.sem_flg = IPC_NOWAIT|SEM_UNDO;
/*	do {
		stat = semop (semId, &up, 1);
	} while ((stat == -1) && (errno == EINTR));*/
	stat =  sem_post( sem );
	if( 0 != stat ){
		OneInstanceLogger::instance()->log(modName,M_LOG_LOW,M_LOG_ERR,"Eint_down():this=%p:statsemop=%d:errno=%d:msg=%s",this,stat,errno, strerror(errno) );
		return -1;
	}

	actualValue++;
	stat = sem_getvalue(sem , &actVal );
	OneInstanceLogger::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"Eup():this=%p:val=%d",this,actVal);
	return stat;
}

int JPSemaphore::initSem(){
	OneInstanceLogger::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"initSem():this=%p",this);
	for( int i = 0 ; i < maxValue ; i++ )
		up();
	return 0;
}


JPBinSemaphore::JPBinSemaphore( int semId , int sValue )
:JPSemaphore( semId , sValue )
{
	this->maxValue = 1;
}

JPBinSemaphore::JPBinSemaphore()
:JPSemaphore()
{
	OneInstanceLogger::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"JPBinSemaphore()");
	this->maxValue = 1;

	OneInstanceLogger::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"EJPBinSemaphore(%d,%d):this=%p",semId,actualValue,this);
}
int
JPBinSemaphore::initSem(){
	OneInstanceLogger::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"initSem():this=%p",this);
	up();
	return 0;
}
JPBinSemaphore::~JPBinSemaphore()
{

	int res = sem_close(sem);

}
int
JPBinSemaphore::up(){
	OneInstanceLogger::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"up():this=%p,id[%d]",this,semId);
	if( this->maxValue != this->actualValue )
		return int_up();
	return -1;
}
