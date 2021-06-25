#include "simplefs-ops.h"
extern struct filehandle_t file_handle_array[MAX_OPEN_FILES]; // Array for storing opened files
//file_handle_array to the compiler defined in header simplefs-disk.h

#define NO_FILE -1 //check flag for file removed

int file_available(char *filename){
    inode_num = -1;		//physical file
				//inode_number initialized in simplefs-disk
    struct inode_t file_inode; //struct from simplefs-disk.h
    int i = 0;
    for (i = 0; i < NUM_INODES; i++)
    {
        simplefs_readInode(i, inode_t *inodeptr);	//reads the specified inode from disk and copies it into the inode pointer
        if (file_inode.status == INODE_IN_USE)
	{
            if (file_inode.name == filename) 
	    {
                inode_num = i;
		break;
            }
        }
    }
    return inode_num;
}

//first
int simplefs_create(char *filename){
    /*
	    Create file with name `filename` from disk
	*/
    //first check if the file name exists
    if (file_available(filename) != NO_FILE)
    {
	    return -1;       //if file not exists --> exit
    }

     //Disk space availability
    int free_data_block = simplefs_allocDataBlock(); 	//allocates a free data block
    if (free_data_block == -1)
    {
	    return -1;	//if no free block can be found
    }
	
    // inode availibilty
    int  inode_num = simplefs_allocInode(); 	//allocates a free inode on disk
    if (inode_num == -1)	//Inode number for the file
    {
	return -1;	//if no free inode can be found
    }
	
    struct inode_t file_inode;    
    simplefs_readInode(inode_num, file_inode *inodeptr);
    file_inode.name = filename;   //create filename
    return inode_num;
}


//second
void simplefs_delete(char *filename){
    /*
	    delete file with name `filename` from disk
	*/
    int inode_num = file_available(filename);
    if (inode_num != NO_FILE)
    {
      	//Free datablock
        struct inode_t file_inode;
        simplefs_readInode(inode_num, &file_inode);
        int index_handle;   //index block data
        for (index_handle = 0; index_handle < MAX_FILE_SIZE; index_handle++) //called from simplefs-disk
        {
            if (file_inode.direct_blocks[index_handle] != DATA_BLOCK_FREE)
                simplefs_freeDataBlock(file_inode.direct_blocks[index_handle])
        }
        simplefs_freeInode(inode_num)	//frees up the specified inode,by marking it as free in the superblock
    }
}


/*int simplefs_open(char *filename){
    int fd = open(filename, "r");
    if (fd ==-1)
    {
        // print which type of error have in a code
        printf("Error);
     }
     else{
     	return -1;
    }
    */


//third
int simplefs_open(char *filename){
    /*
	    open file with name `filename`
	*/
	//for existing files
    int inode_num = file_available(filename);
    int index_newly_allocated = -1;	//index allocated
    if (inode_num != NO_FILE)
    {
           for (int i=0; i < MAX_OPEN_FILES; i++)
	   {
		   if (file_handle_array[i].inode_number == -1)
		   {
                   	index_newly_allocated = i;
                   	file_handle_array[i].inode_number = inode_num;
                  	return index_newly_allocated;	//returnsthe index of the newly allocated file handle
		   }
		   else
		   {
			   return -1; //the file open failed for any reason
		   }
           }
    }
}


//fourth
void simplefs_close(int file_handle){
    /*
	    close file pointed by `file_handle`
	*/
	/* The state of open files in the system (the inode number and the offset of reading/writing)
is captured in a file handle of an open file.*/
	
    //int inode_number = -1;
    //int offset = 0;
    //close(file_handle).inode_number; //close file handler and append new inode number
    //return file_handle.offset;
	
    file_handle_array[file_handle].inode_number = -1;  //end of file
    file_handle_array[file_handle].offset = 0;	//file handler offset set to zero 
}


//fifth
int simplefs_read(int file_handle, char *buf, int nbytes){
    /*
	    read `nbytes` of data into `buf` from file pointed by `file_handle` starting at current offset
	*/
    int read_file_offset = file_handle_array[file_handle].offset;	
    if (file_handle_array[file_handle].offset + nbytes < nbytes * BLOCKSIZE)
    {
	file_handle_array[file_handle].offset = read_file_offset + nbytes;
	    
	simplefs readDataBlock(int file_handle.offset, char *buf);
	
	break;
    }
    else{
	return -1;
    }
}


int simplefs_write(int file_handle, char *buf, int nbytes){
    /*
	    write `nbytes` of data from `buf` to file pointed by `file_handle` starting at current offset
	*/
    return -1;
}


int simplefs_seek(int file_handle, int nseek){
    /*
	   increase `file_handle` offset by `nseek`
	*/
    return -1;
}
