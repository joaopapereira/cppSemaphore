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
 *  along with libJPSemaphores.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef libJPSemaphores_H
#define libJPSemaphores_H
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * Class used to implement a unique counter
 * for the identifier of the semaphores
 */
class JPSemaphoreId{
public:
	/**
	 * Function used to retrieve the next generated identifier
	 * @return Integer with the next identifier
	 */
	static int getnextId();
private:
	/**
	 * Actual value of the identifier
	 */
	static int semIdentifier;
};


/**
 * Function that implements a Semaphore
 */
class JPSemaphore{
protected:
	/**
	 * Maximum value alowed of the semaphore
	 */
	int	maxValue;
	/**
	 * Actual value of the semaphore
	 */
	int	actualValue;
	/**
	 * Semaphore ID
	 */
	short unsigned int	semId;

	sem_t	*sem;

	/**
	 * Function used in the initialization of the semaphore
	 * @return Integer < 0 in case of Error and 0 in case of success
	 */
	int	initSem();

public:
	/**
	 * Function used to create the semaphore
	 * @param pShared argument indicates whether this semaphore is to be shared
	 * between the threads of a process, or between processes( if 0 is shared between
	 * threads, if nonzero is shared is shared between process)
	 * @param sValue Starting value of the semaphore
	 */
	JPSemaphore( int pShared , int sValue );

	/**
	 * Function used to create the semaphore<br>
	 * The function creates a semaphore to use in threads and starting value equal
	 * to 1
	 */
	JPSemaphore( );

	/**
	 * Function used to destruct the semaphore.<br>
	 * This function call the system call to delete the semaphore from the system
	 */
	~JPSemaphore();

	/**
	 * Function increments the value of the semaphore.<br>
	 * When this function is called all the threads/process holding in this semaphore
	 * are woke.
	 * @return Return -1 on Error and 0 on Success
	 */
	int up();

	/**
	 * Function decrements the value of the semaphore.<br>
	 * If the semaphore is zero puts the thread/process on hold.<br>
	 * If the semaphore is nonzero decrements the semaphore value
	 * @return Return -1 on Error and 0 on Success
	 */
	int down();

protected:
	/**
	 * Function increments the value of the semaphore.<br>
	 * When this function is called all the threads/process holding in this semaphore
	 * are woke.
	 * @return Return -1 on Error and 0 on Success
	 */
	int int_up();
	/**
	 * Function decrements the value of the semaphore.<br>
	 * If the semaphore is zero puts the thread/process on hold.<br>
	 * If the semaphore is nonzero decrements the semaphore value
	 * @return Return -1 on Error and 0 on Success
	 */
	int int_down();

	/**
	 * Function that creates the semaphore
	 */
	void int_createSem();
};

/**
 * Specialization of the semaphore.
 * This class implements a binary semaphore
 */
class JPBinSemaphore: public JPSemaphore{
protected:
	/**
	 * Initializes the semaphore
	 */
	int	initSem();

public:
	/**
	 * Function used to create the semaphore
	 * @param pShared argument indicates whether this semaphore is to be shared
	 * between the threads of a process, or between processes( if 0 is shared between
	 * threads, if nonzero is shared is shared between process)
	 * @param sValue Starting value of the semaphore
	 */
	JPBinSemaphore( int pShared , int sValue );

	/**
	 * Function used to create the semaphore<br>
	 * The function creates a semaphore to use in threads and starting value equal
	 * to 1
	 */
	JPBinSemaphore( );

	/**
	 * Function used to destruct the semaphore.<br>
	 * This function call the system call to delete the semaphore from the system
	 */
	~JPBinSemaphore();

	/**
	 * Function increments the value of the semaphore.<br>
	 * When this function is called all the threads/process holding in this semaphore
	 * are woke. If actual value = 1 does nothing
	 * @return Return -1 on Error and 0 on Success
	 */
	int up();

};

#endif
