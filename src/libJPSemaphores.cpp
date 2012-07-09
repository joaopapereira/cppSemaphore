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
#include "libJPSemaphores.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <iostream>
#include "MLog.hpp"
#include <string.h>
#include <stdlib.h>

#define _SEMBASEMASK 0666
#define _SEMDEFID 1234
#define _SEMDEFVAL 0
#define _SEMDEFMAX 1

int MSemaphoreId::semIdentifier = 1000;
int MSemaphoreId::getnextId(){
	return semIdentifier++;
}


static std::string modName("SEM");
MSemaphore::MSemaphore( int semId , int sValue )
{
//	sem_init( &sem , pShared , sValue );
	MLog::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"MSemaphore(%d,%d)",semId,sValue);
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
		MLog::instance()->log(modName,M_LOG_LOW,M_LOG_ERR,"EMSemaphore(%d,%d):this=%p:errno",semId,actualValue,this,errno);
	}
	free( semName );
	MLog::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"EMSemaphore(%d,%d):this=%p",semId,actualValue,this);
}

MSemaphore::MSemaphore()
{
	MLog::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"MSemaphore()");
//	sem_init( &sem , 0 , 1 );
	semId = MSemaphoreId::getnextId();
	MLog::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"semId(%d)",semId);
	actualValue = _SEMDEFVAL;
	maxValue = _SEMDEFMAX;
	MLog::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"actualValue(%d), maxValue(%d)", actualValue,maxValue);
	//char * semName = (char*)malloc( sizeof(char) * 50);
	char semName[50];
	//char semName[100];
	MLog::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"done alloc");
	sprintf(semName,"M%d_%d",semId,getpid());
	MLog::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"semname(%s)",semName);
	sem = sem_open(semName, O_CREAT , S_IRUSR|S_IWUSR, 0);
	//if( res != -1 )
	if( SEM_FAILED != sem )
		initSem();
	//free( semName );
	MLog::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"EMSemaphore(%d,%d):this=%p",semId,actualValue,this);
}

MSemaphore::~MSemaphore()
{
	//int res = (semctl (semId, 0, IPC_RMID, NULL));
	int res = sem_close(sem);
	if( res == 0 )
		initSem();
//	sem_destroy( &sem );
}

int MSemaphore::signal()
{
	/*struct sembuf up = { 0, 1, 0 };
	return (semop (semId, &up, 1));*/
	//return sem_post(&sem);
}

int MSemaphore::connect()
{
/*
	int result = sem_wait( &sem );
	char answer[100];
	sprintf(answer,"result:[%d], errno:[%d] sem:[%p] down!",result,errno,&sem);
	std::cerr << answer<< std::endl;
	return result;*/
	/*
	struct sembuf init[2] = {{ 0, -1, 0 }, {0, 1, 0}};
	if ((semId = semget ((key_t) semId, 1, _SEMBASEMASK)) == -1)
		return (-1);
	else if( semop (semId, init, 2) == -1)
		return (-1);
	else return (semId);
*/
}
int MSemaphore::down(){
	MLog::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"down():this=%p,id[%d]",this,semId);
	return int_down();
}
int MSemaphore::int_down(){
	MLog::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"int_down():this=%p,id[%d]",this,semId);
//	struct sembuf down = { semId, -1, SEM_UNDO };
	int stat,actVal;

//	down.sem_num = (unsigned short) semId;
//	down.sem_op = -1;
//	down.sem_flg = SEM_UNDO;
	/*do {
		stat = semop (semId, &down, 1);
		MLog::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"Edown():this=%p:statsemop=%d:errno=%d:msg=%s",this,stat,errno, strerror(errno) );
	}while((stat == -1) && (errno == EINTR));*/
	stat =  sem_wait( sem );
	if( 0 != stat ){
		MLog::instance()->log(modName,M_LOG_LOW,M_LOG_ERR,"Edown():this=%p:statsemop=%d:errno=%d:msg=%s",this,stat,errno, strerror(errno) );
		return -1;
	}
	actualValue--;
	stat = sem_getvalue(sem , &actVal );
	MLog::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"Eint_down():this=%p:val=%d",this,actVal);

	return stat;
}

int MSemaphore::tryDown()
{
	//return sem_trywait( &sem );
	return 0;
}
int MSemaphore::up(){
	MLog::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"up():this=%p,id[%d]",this,semId);
	return int_up();
}
int MSemaphore::int_up(){
	MLog::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"int_up():this=%p,id[%d]",this,semId);
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
		MLog::instance()->log(modName,M_LOG_LOW,M_LOG_ERR,"Eint_down():this=%p:statsemop=%d:errno=%d:msg=%s",this,stat,errno, strerror(errno) );
		return -1;
	}

	actualValue++;
	stat = sem_getvalue(sem , &actVal );
	MLog::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"Eup():this=%p:val=%d",this,actVal);
	return stat;
}

int MSemaphore::initSem(){
	MLog::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"initSem():this=%p",this);
	for( int i = 0 ; i < maxValue ; i++ )
		up();
	return 0;
}
int MSemaphore::value(){
	return actualValue;
}


MBinSemaphore::MBinSemaphore( int semId , int sValue )
:MSemaphore( semId , sValue )
{
	this->maxValue = 1;
}

MBinSemaphore::MBinSemaphore()
:MSemaphore()
{
	MLog::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"MBinSemaphore()");
	this->maxValue = 1;

	MLog::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"EMBinSemaphore(%d,%d):this=%p",semId,actualValue,this);
}
int
MBinSemaphore::initSem(){
	MLog::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"initSem():this=%p",this);
	up();
	return 0;
}
int
MBinSemaphore::up(){
	MLog::instance()->log(modName,M_LOG_LOW,M_LOG_TRC,"up():this=%p,id[%d]",this,semId);
	if( this->maxValue != this->actualValue )
		return int_up();
	return -1;
}
