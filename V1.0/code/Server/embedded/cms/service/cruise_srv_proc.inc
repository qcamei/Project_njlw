#ifndef __CRUISE_SRV_PROC_H__
#define __CRUISE_SRV_PROC_H__


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

    /* Ѳ�������ṹ�� */
    typedef struct _cruise_action_t
    {
        unsigned int device_index;  /* Ѳ�����߼��豸���� */
        unsigned int iPresetID;     /* Ԥ��λID */
        int iStatus;                /* Ѳ��״̬:0:û��Ѳ����1:����Ѳ�� */
        int iLiveTime;              /* ͣ��ʱ�� */
        int iLiveTimeCount;         /* ͣ��ʱ����� */
        int del_mark;               /* ɾ����ʶ */
    } cruise_action_t;

    /* Ѳ��ҵ��ṹ�� */
    typedef struct _cruise_srv__t
    {
        unsigned int cruise_id;                             /* Ѳ��id */
        int status;                                         /* ״̬: 0:û��Ѳ����1:����Ѳ����2:��Ҫ����Ѳ��, 3:��ҪֹͣѲ��, 4:��Ҫ����֪ͨ���ͻ��� */
        int cruise_type;                                    /* Ѳ������:0:����Ѳ��, 1: Ԥ������ִ�е�Ѳ����2:����Ѳ��ִ���м���ִ��Ԥ��������Ѳ��, 3:Ԥ��ִ�е�Ѳ���м��ֱ��û��ֶ�ִ�� */
        char cruise_name[MAX_128CHAR_STRING_LEN + 4];       /* Ѳ������ */
        int start_time;                                     /* ��ʼʱ�� */
        int duration_time;                                  /* ����ʱ�� */
        int duration_time_count;                            /* ����ʱ����� */
        int current_pos;                                    /* ��ǰѲ����pos */

        int del_mark;                                       /* ɾ����ʶ */
        int send_mark;                                      /* ���ͱ�ʶ */
        osip_list_t* pCruiseActionList;                     /* Ѳ������ */
    } cruise_srv_t;

    /* Ѳ��ҵ����� */
    typedef struct _cruise_srv_list_t
    {
        osip_list_t* pCruiseSrvList;
#ifdef MULTI_THR
        osip_mutex_t* lock;
#endif
    } cruise_srv_list_t;

    /* ������Ѳ��ҵ����� */
    typedef std::deque <cruise_srv_t*> needtoproc_cruisesrv_queue;

    extern int add_cruise_action_data_to_srv_list_proc(unsigned int cruise_id, osip_list_t* pCruiseActionList, DBOper* pCruise_Srv_dboper);
    extern void check_CruiseSrvConfig_need_to_reload_begin(DBOper* pDboper);
    extern void check_CruiseSrvConfig_need_to_reload_end();
    extern int check_db_data_to_cruise_srv_list(DBOper* pCruise_Srv_dboper);
    extern int CruiseSrvConfig_db_refresh_proc();
    extern int cruise_action_find(unsigned int device_index, unsigned int iPresetID, osip_list_t* pCruiseActionList);
    extern void cruise_action_free(cruise_action_t* cruise_action);
    extern cruise_action_t* cruise_action_get(int pos, osip_list_t* pCruiseActionList);
    extern int cruise_action_init(cruise_action_t** cruise_action);
    extern int cruise_action_proc(cruise_srv_t* pCruiseSrv);
    extern int cruise_action_release(cruise_srv_t* pCruiseSrv);
    extern int cruise_action_stop(cruise_srv_t* pCruiseSrv);
    extern int cruise_srv_add(cruise_srv_t* pCruiseSrv);
    extern int cruise_srv_find(unsigned int id);
    extern void cruise_srv_free(cruise_srv_t* cruise_srv);
    extern cruise_srv_t* cruise_srv_get(int pos);
    extern int cruise_srv_init(cruise_srv_t** cruise_srv);
    extern void cruise_srv_list_free();
    extern int cruise_srv_list_init();
    extern int cruise_srv_list_lock();
    extern int cruise_srv_list_unlock();
    extern int cruise_srv_remove(int pos);
    extern int debug_cruise_srv_list_lock(const char* file, int line, const char* func);
    extern int debug_cruise_srv_list_unlock(const char* file, int line, const char* func);
    extern void delete_cruise_srv_data();
    extern int get_user_index_from_user_cruise_config(char* pcCruiseID, vector<unsigned int>& UserIndexVector, DBOper* pDBOper);
    extern void scan_cruise_srv_list(DBOper* pCruise_Srv_dboper);
    extern int SendNotifyExecuteCruiseActionToOnlineUser(unsigned int uCruiseID, char* cruise_name, int iType, DBOper* pCruise_Srv_dboper);
    extern int set_cruise_srv_list_del_mark(int del_mark);
    extern void ShowCruiseTaskInfo(int sock, int status);
    extern int start_cruise_srv_by_id(user_info_t* pUserInfo, unsigned int id, DBOper* pCruise_Srv_dboper);
    extern int start_cruise_srv_by_id_for_plan(unsigned int id, DBOper* pCruise_Srv_dboper);
    extern int StopAllCruiseTask(int sock);
    extern int StopCruiseTask(int sock, unsigned int cruise_id);
    extern int stop_cruise_srv_by_id(unsigned int id);
    extern int UpdateCruiseConfigStatus2DB(int cruise_id, int status, DBOper* pCruise_Srv_dboper);

#ifdef ENABLE_DEBUG_LOCK
#define CRUISE_SMUTEX_LOCK() debug_cruise_srv_list_lock(__FILE__, __LINE__, __func__)
#define CRUISE_SMUTEX_UNLOCK() debug_cruise_srv_list_unlock(__FILE__, __LINE__, __func__)
#else
#define CRUISE_SMUTEX_LOCK() cruise_srv_list_lock()
#define CRUISE_SMUTEX_UNLOCK() cruise_srv_list_unlock()
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __UDP_TL_H__ */