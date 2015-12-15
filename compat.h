/*
 * Declarations to provide compatibility with all kernel versions from
 * 2.6.25 up, without littering the code with #ifdefs all over.
 */

#include <linux/version.h>


/*
 * The prototypes for open() and release() in struct block_device_operations
 * changed considerably in 2.6.28.
 */

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,28)

#define COMPAT_OPEN_PARAMS		struct inode *inode, struct file *filp
#define COMPAT_RELEASE_PARAMS		struct inode *inode, struct file *filp
#define compat_open_get_disk()		(inode->i_bdev->bd_disk)
#define compat_release_get_disk()	(inode->i_bdev->bd_disk)
#define compat_open_get_bdev()		(inode->i_bdev)

#else

#define COMPAT_OPEN_PARAMS		struct block_device *bdev, fmode_t mode
#define COMPAT_RELEASE_PARAMS		struct gendisk *disk, fmode_t mode
#define compat_open_get_disk()		(bdev->bd_disk)
#define compat_release_get_disk()	disk
#define compat_open_get_bdev()		bdev

#endif


/* hardsect_size was renamed to logical_block_size in 2.6.31 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,31)
# define blk_queue_logical_block_size blk_queue_hardsect_size
#endif

/* This was defined in 2.6.28 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,28)
# define disk_to_dev(disk)	(&(disk)->dev)
#endif

/* struct tty_ldisc was renamed to tty_ldisc_ops in 2.6.27 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,27)
# define tty_ldisc_ops tty_ldisc
#endif

/* tty_operations were moved to tty->ops in 2.6.26 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,26)
# define compat_tty_write(tty)		tty->driver->write
#else
# define compat_tty_write(tty)		tty->ops->write
#endif

/* (*make_request_fn)() returns void starting from 3.2 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,2,0)
# define COMPAT_REQUEST_RETTYPE		int
# define COMPAT_REQUEST_RETURN(ret)	return(ret)
#else
# define COMPAT_REQUEST_RETTYPE		void
# define COMPAT_REQUEST_RETURN(ret)	return
#endif

/* block_device_operations->release() returns void since 3.10 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0)
# define COMPAT_RELEASE_RETTYPE         int
# define COMPAT_RELEASE_RETURN(ret)     return(ret)
#else
# define COMPAT_RELEASE_RETTYPE         void
# define COMPAT_RELEASE_RETURN(ret)     return
#endif

/* bio->bi_sector moved to bio->bi_iter.bi_sector in 3.14 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,14,0)
# define compat_bio_bi_sector(bio)        bio->bi_sector
#else
# define compat_bio_bi_sector(bio)        bio->bi_iter.bi_sector
#endif

/* bio_for_each_segment() argument types changed in 3.14 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,14,0)
# define COMPAT_BIO_VEC_TYPE            struct bio_vec *
# define COMPAT_BVEC_ITER_TYPE          int
# define compat_bvec(bvec)              (*bvec)
#else
# define COMPAT_BIO_VEC_TYPE            struct bio_vec
# define COMPAT_BVEC_ITER_TYPE          struct bvec_iter
# define compat_bvec(bvec)              bvec
#endif

/* bio errors are signaled via bio->bi_error since 4.3 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(4,3,0)
# define compat_bio_endio(bio, error)   bio_endio(bio, error)
#else
# define compat_bio_endio(bio, error)   bio->bi_error = error; bio_endio(bio)
#endif
