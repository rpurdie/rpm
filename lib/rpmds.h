#ifndef H_RPMDS
#define H_RPMDS

/** \ingroup rpmdep rpmtrans
 * \file lib/rpmds.h
 * Structure used for handling a dependency set.
 */

/**
 */
typedef struct sharedFileInfo_s *		sharedFileInfo;

/**
 */
struct sharedFileInfo_s {
    int pkgFileNum;
    int otherFileNum;
    int otherPkg;
    int isRemoved;
};

/**
 * A package filename set.
 */
struct rpmFNSet_s {
    int i;			/*!< File index. */

/*@observer@*/
    const char * Type;		/*!< Tag name. */

    rpmTag tagN;		/*!< Header tag. */
/*@refcounted@*/ /*@null@*/
    Header h;			/*!< Header for file name set (or NULL) */

/*@only@*/ /*?null?*/
    const char ** bnl;		/*!< Base name(s) (from header) */
/*@only@*/ /*?null?*/
    const char ** dnl;		/*!< Directory name(s) (from header) */

/*@only@*/ /*?null?*/
    const char ** fmd5s;	/*!< File MD5 sum(s) (from header) */
/*@only@*/ /*?null?*/
    const char ** flinks;	/*!< File link(s) (from header) */
/*@only@*/ /*?null?*/
    const char ** flangs;	/*!< File lang(s) */

/*@only@*/ /*?null?*/
          uint_32 * dil;	/*!< Directory indice(s) (from header) */
/*@only@*/ /*?null?*/
    const uint_32 * fflags;	/*!< File flag(s) (from header) */
/*@only@*/ /*?null?*/
    const uint_32 * fsizes;	/*!< File size(s) (from header) */
/*@only@*/ /*?null?*/
    const uint_32 * fmtimes;	/*!< File modification time(s) (from header) */
/*@only@*/ /*?null?*/
          uint_16 * fmodes;	/*!< File mode(s) (from header) */
/*@only@*/ /*?null?*/
    const uint_16 * frdevs;	/*!< File rdev(s) (from header) */

/*@only@*/ /*@null@*/
    const char ** fuser;	/*!< File owner(s) */
/*@only@*/ /*@null@*/
    const char ** fgroup;	/*!< File group(s) */
/*@only@*/ /*@null@*/
    uid_t * fuids;		/*!< File uid(s) */
/*@only@*/ /*@null@*/
    gid_t * fgids;		/*!< File gid(s) */

/*@only@*/ /*@null@*/
    char * fstates;		/*!< File state(s) (from header) */

    int_32 dc;			/*!< No. of directories. */
    int_32 fc;			/*!< No. of files. */

/*=============================*/
/*@owned@*/
    const char * name;		/*!< Name: tag (malloc'd). */
/*@owned@*/
    const char * version;	/*!< Version: tag (malloc'd). */
/*@owned@*/
    const char * release;	/*!< Release: tag (malloc'd). */
    uint_32 multiLib;		/* MULTILIB */
/*@null@*/
    fnpyKey key;		/*!< Package notify key. */
/*@null@*/ /*@dependent@*/
    rpmRelocation * relocs;	/*!< Package file relocations. */
/*@null@*/
    FD_t fd;			/*!< Package file handle */
    rpmTransactionType type;
    HGE_t hge;			/*!< Vector to headerGetEntry() */
    HAE_t hae;			/*!< Vector to headerAddEntry() */
    HME_t hme;			/*!< Vector to headerModifyEntry() */
    HRE_t hre;			/*!< Vector to headerRemoveEntry() */
    HFD_t hfd;			/*!< Vector to headerFreeData() */
    int_32 epoch;
/*-----------------------------*/
    uid_t uid;			/*!< File uid (default). */
    gid_t gid;			/*!< File gid (default). */
    uint_32 flags;		/*!< File flags (default). */
    fileAction action;		/*!< File disposition (default). */
/*@owned@*/
    fileAction * actions;	/*!< File disposition(s). */
/*@owned@*/
    struct fingerPrint_s * fps;	/*!< File fingerprint(s). */
/*@owned@*/
    const char ** obnl;		/*!< Original basename(s) (from header) */
/*@owned@*/
    const char ** odnl;		/*!< Original dirname(s) (from header) */
/*@unused@*/
    int_32 * odil;		/*!< Original dirindex(s) (from header) */
    int bnlmax;			/*!< Length (in bytes) of longest basename. */
    int dnlmax;			/*!< Length (in bytes) of longest dirname. */
    int astriplen;
    int striplen;
    unsigned int archiveSize;
    mode_t dperms;		/*!< Directory perms (0755) if not mapped. */
    mode_t fperms;		/*!< File perms (0644) if not mapped. */
/*@only@*/ /*@null@*/
    const char ** apath;
    int mapflags;
/*@owned@*/ /*@null@*/
    int * fmapflags;
/*@owned@*/
    FSM_t fsm;			/*!< File state machine data. */
    int keep_header;		/*!< Keep header? */
/*@owned@*/
    sharedFileInfo replaced;	/*!< (TR_ADDED) */
/*@owned@*/
    uint_32 * replacedSizes;	/*!< (TR_ADDED) */
    unsigned int record;	/*!< (TR_REMOVED) */
    int magic;
#define	TFIMAGIC	0x09697923
/*=============================*/

/*@refs@*/ int nrefs;		/*!< Reference count. */
};

/**
 * A package dependency set.
 */
struct rpmDepSet_s {
    int i;			/*!< Element index. */

/*@observer@*/
    const char * Type;		/*!< Tag name. */
/*@only@*/ /*@null@*/
    const char * DNEVR;		/*!< Formatted dependency string. */

    rpmTag tagN;		/*!< Header tag. */
/*@refcounted@*/ /*@null@*/
    Header h;			/*!< Header for dependency set (or NULL) */

/*@only@*/
    const char ** N;		/*!< Name. */
/*@only@*/
    const char ** EVR;		/*!< Epoch-Version-Release. */
/*@only@*/
    int_32 * Flags;		/*!< Flags identifying context/comparison. */
    rpmTagType Nt, EVRt, Ft;	/*!< Tag data types. */
    int_32 Count;		/*!< No. of elements */
/*@refs@*/ int nrefs;		/*!< Reference count. */
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Unreference a file info set instance.
 * @param fns		file info set
 * @return		NULL always
 */
/*@unused@*/ /*@null@*/
rpmFNSet rpmfnsUnlink (/*@killref@*/ /*@only@*/ /*@null@*/ rpmFNSet fns,
		/*@null@*/ const char * msg)
	/*@modifies fns @*/;

/** @todo Remove debugging entry from the ABI. */
/*@-exportlocal@*/
/*@null@*/
rpmFNSet XrpmfnsUnlink (/*@killref@*/ /*@only@*/ /*@null@*/ rpmFNSet fns,
		/*@null@*/ const char * msg, const char * fn, unsigned ln)
	/*@modifies fns @*/;
/*@=exportlocal@*/
#define	rpmfnsUnlink(_fns, _msg) XrpmfnsUnlink(_fns, _msg, __FILE__, __LINE__)

/**
 * Reference a file info set instance.
 * @param fns		file info set
 * @return		new file info set reference
 */
/*@unused@*/
rpmFNSet rpmfnsLink (/*@null@*/ rpmFNSet fns, /*@null@*/ const char * msg)
	/*@modifies fns @*/;

/** @todo Remove debugging entry from the ABI. */
rpmFNSet XrpmfnsLink (/*@null@*/ rpmFNSet fns, /*@null@*/ const char * msg,
		const char * fn, unsigned ln)
        /*@modifies fns @*/;
#define	rpmfnsLink(_fns, _msg)	XrpmfnsLink(_fns, _msg, __FILE__, __LINE__)

/**
 * Destroy a file name set.
 * @param ds		file name set
 * @return		NULL always
 */
/*@null@*/
rpmFNSet fnsFree(/*@killref@*/ /*@only@*/ /*@null@*/ rpmFNSet fns)
	/*@modifies fns@*/;

/**
 * Create and load a file name set.
 * @param h		header
 * @param tagN		RPMTAG_BASENAMES
 * @param scareMem	Use pointers to refcounted header memory?
 * @return		new file name set
 */
/*@null@*/
rpmFNSet fnsNew(Header h, rpmTag tagN, int scareMem)
	/*@modifies h @*/;

/**
 * Unreference a dependency set instance.
 * @param ds		dependency set
 * @return		NULL always
 */
/*@unused@*/ /*@null@*/
rpmDepSet rpmdsUnlink (/*@killref@*/ /*@only@*/ /*@null@*/ rpmDepSet ds,
		/*@null@*/ const char * msg)
	/*@modifies ds @*/;

/** @todo Remove debugging entry from the ABI. */
/*@-exportlocal@*/
/*@null@*/
rpmDepSet XrpmdsUnlink (/*@killref@*/ /*@only@*/ /*@null@*/ rpmDepSet ds,
		/*@null@*/ const char * msg, const char * fn, unsigned ln)
	/*@modifies ds @*/;
/*@=exportlocal@*/
#define	rpmdsUnlink(_ds, _msg)	XrpmdsUnlink(_ds, _msg, __FILE__, __LINE__)

/**
 * Reference a dependency set instance.
 * @param ds		dependency set
 * @return		new dependency set reference
 */
/*@unused@*/
rpmDepSet rpmdsLink (/*@null@*/ rpmDepSet ds, /*@null@*/ const char * msg)
	/*@modifies ds @*/;

/** @todo Remove debugging entry from the ABI. */
rpmDepSet XrpmdsLink (/*@null@*/ rpmDepSet ds, /*@null@*/ const char * msg,
		const char * fn, unsigned ln)
        /*@modifies ds @*/;
#define	rpmdsLink(_ds, _msg)	XrpmdsLink(_ds, _msg, __FILE__, __LINE__)

/**
 * Destroy a dependency set.
 * @param ds		dependency set
 * @return		NULL always
 */
/*@null@*/
rpmDepSet dsFree(/*@killref@*/ /*@only@*/ /*@null@*/ rpmDepSet ds)
	/*@modifies ds@*/;
/**
 * Create and load a dependency set.
 * @param h		header
 * @param tagN		type of dependency
 * @param scareMem	Use pointers to refcounted header memory?
 * @return		new dependency set
 */
/*@null@*/
rpmDepSet dsNew(Header h, rpmTag tagN, int scareMem)
	/*@modifies h @*/;

/**
 * Return new formatted dependency string.
 * @param dspfx		formatted dependency string prefix
 * @param ds		dependency set
 * @return		new formatted dependency (malloc'ed)
 */
/*@only@*/
char * dsDNEVR(const char * dspfx, const rpmDepSet ds)
	/*@*/;

/**
 * Create, load and initialize a dependency for this header. 
 * @param h		header
 * @param tagN		type of dependency
 * @param Flags		comparison flags
 * @return		new dependency set
 */
/*@null@*/
rpmDepSet dsThis(Header h, rpmTag tagN, int_32 Flags)
	/*@*/;

/**
 * Create, load and initialize a dependency set of size 1.
 * @param tagN		type of dependency
 * @param N		name
 * @param EVR		epoch:version-release
 * @param Flags		comparison flags
 * @return		new dependency set
 */
/*@null@*/
rpmDepSet dsSingle(rpmTag tagN, const char * N, const char * EVR, int_32 Flags)
	/*@*/;

/**
 * Return dependency set count.
 * @param ds		dependency set
 * @return		current count
 */
int dsiGetCount(/*@null@*/ rpmDepSet ds)
	/*@*/;

/**
 * Return dependency set index.
 * @param ds		dependency set
 * @return		current index
 */
int dsiGetIx(/*@null@*/ rpmDepSet ds)
	/*@*/;

/**
 * Set dependency set index.
 * @param ds		dependency set
 * @param ix		new index
 * @return		current index
 */
int dsiSetIx(/*@null@*/ rpmDepSet ds, int ix)
	/*@modifies ds @*/;

/**
 * Return current formatted dependency string.
 * @param ds		dependency set
 * @return		current dependency DNEVR, NULL on invalid
 */
/*@null@*/
const char * dsiGetDNEVR(/*@null@*/ rpmDepSet ds)
	/*@*/;

/**
 * Return current dependency name.
 * @param ds		dependency set
 * @return		current dependency name, NULL on invalid
 */
/*@null@*/
const char * dsiGetN(/*@null@*/ rpmDepSet ds)
	/*@*/;

/**
 * Return current dependency epoch-version-release.
 * @param ds		dependency set
 * @return		current dependency EVR, NULL on invalid
 */
/*@null@*/
const char * dsiGetEVR(/*@null@*/ rpmDepSet ds)
	/*@*/;

/**
 * Return current dependency Flags.
 * @param ds		dependency set
 * @return		current dependency EVR, 0 on invalid
 */
int_32 dsiGetFlags(/*@null@*/ rpmDepSet ds)
	/*@*/;

/**
 * Notify of results of dependency match;
 * @param ds		dependency set
 * @param where		where dependency was resolved (or NULL)
 * @param rc		0 == YES, otherwise NO
 */
/*@-globuse@*/ /* FIX: rpmMessage annotation is a lie */
void dsiNotify(/*@null@*/ rpmDepSet ds, /*@null@*/ const char * where, int rc)
	/*@globals fileSystem @*/
	/*@modifies fileSystem @*/;
/*@=globuse@*/

/**
 * Return next dependency set iterator index.
 * @param ds		dependency set
 * @return		dependency set iterator index, -1 on termination
 */
int dsiNext(/*@null@*/ rpmDepSet ds)
	/*@modifies ds @*/;

/**
 * Initialize dependency set iterator.
 * @param ds		dependency set
 * @return		dependency set
 */
/*@null@*/
rpmDepSet dsiInit(/*@returned@*/ /*@null@*/ rpmDepSet ds)
	/*@modifies ds @*/;

/**
 * Compare two versioned dependency ranges, looking for overlap.
 * @param A		1st dependency
 * @param B		2nd dependency
 * @return		1 if dependencies overlap, 0 otherwise
 */
int dsCompare(const rpmDepSet A, const rpmDepSet B)
	/*@*/;

/**
 * Report a Requires: or Conflicts: dependency problem.
 */
void dsProblem(/*@null@*/ rpmProblemSet tsprobs,
		const char * pkgNEVR, const rpmDepSet ds,
		/*@only@*/ /*@null@*/ const fnpyKey * suggestedKeys)
	/*@modifies tsprobs @*/;

/**
 * Compare package provides dependencies from header with a single dependency.
 * @param h		header
 * @param ds		dependency set
 */
int rangeMatchesDepFlags (Header h, const rpmDepSet req)
        /*@modifies h @*/;

/**
 * Compare package name-version-release from header with a single dependency.
 * @deprecated Remove from API when obsoletes is correctly implemented.
 * @param h		header
 * @param req		dependency
 * @return		1 if dependency overlaps, 0 otherwise
 */
int headerMatchesDepFlags(const Header h, const rpmDepSet req)
	/*@*/;

#ifdef __cplusplus
}
#endif

#endif	/* H_RPMDS */
