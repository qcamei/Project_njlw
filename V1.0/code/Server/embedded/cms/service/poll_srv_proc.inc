#ifndef __POLL_SRV_PROC_H__
#define __POLL_SRV_PROC_H__


/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
#include <sys/types.h>
#ifdef WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#endif

#include "libsip.h"
#include "libxml/Packet.h"

#include "common/gbldef.inc"
#include "common/DBOper.h"

#include "user/user_info_mgn.inc"

#include <queue>
#include <vector>
#include <string>
using namespace std;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

    /*----------------------------------------------*
     * �ⲿ����˵��                                 *
     *----------------------------------------------*/

    /*----------------------------------------------*
     * �ⲿ����ԭ��˵��                             *
     *----------------------------------------------*/

    /*----------------------------------------------*
     * �ڲ�����ԭ��˵��                             *
     *----------------------------------------------*/

    /*----------------------------------------------*
     * ȫ�ֱ���                                     *
     *----------------------------------------------*/

    /*----------------------------------------------*
     * ģ�鼶����                                   *
     *----------------------------------------------*/

    /*----------------------------------------------*
     * ��������                                     *
     *----------------------------------------------*/

    /*----------------------------------------------*
     * �궨��                                       *
     *----------------------------------------------*/

    /* ��Ѳ�����ṹ�� */
    typedef struct _poll_action_source_t
    {
        int iStatus;                     /* ��Ѳ״̬:0:û����Ѳ��1:������Ѳ*/
        int iType;                       /* ��Ѳ����:PLANACTION_PC, PLANACTION_TVWALL*/
        char pcSourceID[MAX_ID_LEN + 4]; /* Դ�豸��� */
        int iSourceStreamType;           /* Դ�豸ý�������� */
        int iLiveTime;                   /* ͣ��ʱ�� */
        int iLiveTimeCount;              /* ͣ��ʱ����� */
        int iConnectFlag;                /* ���ӵ���ǽ��ʶ: 0:δ�ɹ����Ѿ��ɹ� */
        int iConnectCount;               /* ���Ӽ��� */
        int del_mark;                    /* ɾ����ʶ */
    } poll_action_source_t;

    /* ��Ѳ�����ṹ�� */
    typedef struct _poll_action_t
    {
        unsigned int poll_id;                /* ��Ѳid */
        char pcDestID[MAX_ID_LEN + 4];       /* Ŀ���豸��� */
        int del_mark;                        /* ɾ����ʶ */

        int current_pos;                     /* ��ǰ��Ѳ��source pos */

        osip_list_t* pPollActionSourceList;  /* ��ѲԴ*/
    } poll_action_t;

    /* ��Ѳҵ��ṹ�� */
    typedef struct _poll_srv_t
    {
        unsigned int poll_id;                           /* ��Ѳid */
        int status;                                     /* ״̬: 0:û����Ѳ��1:������Ѳ��2:��Ҫ������Ѳ, 3:��Ҫֹͣ��Ѳ, 4:��Ҫ����֪ͨ���ͻ��� */
        char poll_name[MAX_128CHAR_STRING_LEN + 4];     /* ��Ѳ���� */
        int start_time;                                 /* ��ʼʱ�� */
        int duration_time;                              /* ����ʱ�� */
        int duration_time_count;                        /* ����ʱ����� */
        int del_mark;                                   /* ɾ����ʶ */
        int send_mark;                                  /* ���ͱ�ʶ */
        osip_list_t* pPollActionList;                   /* ��Ѳ���� */
    } poll_srv_t;

    /* ��Ѳҵ����� */
    typedef struct _poll_srv_list_t
    {
        osip_list_t* pPollSrvList;
#ifdef MULTI_THR
        osip_mutex_t* lock;
#endif
    } poll_srv_list_t;

    /* ��������Ѳҵ����� */
    typedef std::deque <poll_srv_t*> needtoproc_pollsrv_queue;

    extern int add_poll_action_dest_data_to_srv_list_proc(unsigned int poll_id, osip_list_t* pPollActionList, DBOper* pPoll_Srv_dboper);
    extern int add_poll_action_source_data_to_srv_list_proc(unsigned int poll_id, char* pcDestID, osip_list_t* pPollActionSourceList, DBOper* pPoll_Srv_dboper);
    extern int check_db_data_to_poll_srv_list(DBOper* pPoll_Srv_dboper);
    extern void check_PollSrvConfig_need_to_reload_begin(DBOper* pDboper);
    extern void check_PollSrvConfig_need_to_reload_end();
    extern int debug_poll_srv_list_lock(const char* file, int line, const char* func);
    extern int debug_poll_srv_list_unlock(const char* file, int line, const char* func);
    extern void delete_poll_srv_data();
    extern int get_user_index_from_user_poll_config(char* pcPollID, vector<unsigned int>& UserIndexVector, DBOper* pDBOper);
    extern poll_action_source_t* next_poll_action_source_get(int current_pos, osip_list_t* pPollActionSourceList);
    extern int PollSrvConfig_db_refresh_proc();
    extern int poll_action_find(char* pcDestID, osip_list_t* pPollActionList);
    extern void poll_action_free(poll_action_t* poll_action);
    extern poll_action_t* poll_action_get(int pos, osip_list_t* pPollActionList);
    extern int poll_action_init(poll_action_t** poll_action);
    extern int poll_action_proc(osip_list_t* pPollActionList);
    extern int poll_action_source_find(char* pcSourceID, osip_list_t* pPollActionSourceList);
    extern void poll_action_source_free(poll_action_source_t* poll_action_source);
    extern int poll_action_source_init(poll_action_source_t** poll_action_source);
    extern int poll_action_stop(osip_list_t* pPollActionList);
    extern int poll_srv_add(poll_srv_t* pPollSrv);
    extern int poll_srv_find(unsigned int id);
    extern void poll_srv_free(poll_srv_t* poll_srv);
    extern poll_srv_t* poll_srv_get(int pos);
    extern int poll_srv_init(poll_srv_t** poll_srv);
    extern void poll_srv_list_free();
    extern int poll_srv_list_init();
    extern int poll_srv_list_lock();
    extern int poll_srv_list_unlock();
    extern int poll_srv_remove(int pos);
    extern void scan_poll_srv_list(DBOper* pPoll_Srv_dboper);
    extern int SendNotifyExecutePollActionToOnlineUser(unsigned int uPollID, char* poll_name, int iType, DBOper* pPoll_Srv_dboper);
    extern int set_poll_srv_list_del_mark(int del_mark);
    extern void ShowPollTaskInfo(int sock, int status);
    extern int start_poll_srv_by_id(user_info_t* pUserInfo, unsigned int id, DBOper* pPoll_Srv_dboper);
    extern int StopAllPollTask(int sock);
    extern int StopPollTask(int sock, unsigned int poll_id);
    extern int stop_poll_srv_by_id(unsigned int id);
    extern int UpdatePollConfigStatus2DB(int poll_id, int status, DBOper* pPoll_Srv_dboper);

#ifdef ENABLE_DEBUG_LOCK
#define POLL_SMUTEX_LOCK() debug_poll_srv_list_lock(__FILE__, __LINE__, __func__)
#define POLL_SMUTEX_UNLOCK() debug_poll_srv_list_unlock(__FILE__, __LINE__, __func__)
#else
#define POLL_SMUTEX_LOCK() poll_srv_list_lock()
#define POLL_SMUTEX_UNLOCK() poll_srv_list_unlock()
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __UDP_TL_H__ */