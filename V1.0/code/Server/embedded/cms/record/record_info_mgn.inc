#ifndef __RECORD_INFO_MGN_H__
#define __RECORD_INFO_MGN_H__


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
    typedef enum _record_status_t
    {
        RECORD_STATUS_INIT,
        RECORD_STATUS_OFFLINE,
        RECORD_STATUS_NOSTREAM,
        RECORD_STATUS_NETWORK_ERROR,
        RECORD_STATUS_NO_TSU,
        RECORD_STATUS_NOT_SUPPORT_MULTI_STREAM,
        RECORD_STATUS_PROC,
        RECORD_STATUS_COMPLETE,
        RECORD_STATUS_NULL
    }
    record_status_t;

    /* ʱ�����ýṹ�� */
    typedef struct _record_time_config_t
    {
        unsigned int uID;                  /* ���ݿ����� */
        int iBeginTime;                    /* ��ʼʱ�� */
        int iEndTime;                      /* ����ʱ�� */
        int iStatus;                       /* ״̬:0:��ͣ��1:�ָ� */
        int del_mark;                      /* ɾ����ʶ */
    } record_time_config_t;

    /* ¼��ʱ�̲��Խṹ�� */
    typedef struct _record_time_sched_t
    {
        unsigned int uID;                  /* ���ݿ����� */
        int record_cr_index;               /* ¼�������Ϣ���� */
        int del_mark;                      /* ɾ����ʶ */

        osip_list_t* pDayOfWeekTimeList;   /* ÿ��ʱ���б� */

    } record_time_sched_t;

    /* ������¼��ʱ����Ϣ���� */
    typedef std::deque <record_time_sched_t*> needtoproc_recordtimesched_queue;

    /* ¼��ʱ����Զ��� */
    typedef struct _record_time_sched_list_t
    {
        osip_list_t* pRecordTimeSchedList;
#ifdef MULTI_THR
        osip_mutex_t* lock;
#endif
    } record_time_sched_list_t;

    /* ¼����Ϣ�ṹ�� */
    typedef struct _record_info_t
    {
        unsigned int uID;                  /* ���ݿ����� */
        unsigned int device_index;         /* �߼��豸���� */
        int stream_type;                   /* ý��������:������������������ */
        int record_enable;                 /* �Ƿ�����¼�� */
        int record_days;                   /* ¼������ */
        int record_timeLen;                /* ¼��ʱ�� */
        int record_type;                   /* ¼������:EV9000_RECORD_TYPE_NORMAL,EV9000_RECORD_TYPE_INTELLIGENCE,EV9000_RECORD_TYPE_ALARM,EV9000_RECORD_TYPE_BACKUP */
        int assign_record;                 /* �Ƿ�ָ��TSU¼�� */
        int assign_tsu_index;              /* ָ��TSU¼���TSU���� */
        int bandwidth;                     /* ǰ�˴���*/
        int TimeOfAllWeek;                 /* �Ƿ�ȫ��¼�� */
        int hasRecordDays;                 /* �Ѿ�¼������ */
        int tsu_index;                     /* ¼���TSU���� */
        int record_cr_index;               /* ¼�������Ϣ���� */
        int record_try_count;              /* ¼���Դ��� */
        int record_retry_interval;         /* ¼���Լ�� */
        record_status_t record_status;     /* ¼��״̬ */
        time_t record_start_time;          /* ¼������ʱ�� */
        int iTSUPauseStatus;               /* �ֶ�¼������£�TSU��ͣ״̬:0:û����ͣ��1:�Ѿ���ͣ */
        int iTSUResumeStatus;              /* �ֶ�¼������£�TSU�ָ�״̬:0:û�лָ���1:�Ѿ��ָ� */
        int iTSUAlarmRecordStatus;         /* ����¼������£�TSU����¼��״̬:0:û��¼��1:�Ѿ�¼�� */
        int del_mark;                      /* ɾ����ʶ:0:��ɾ����1:��Ҫɾ����2:¼����Ҫ���µ���, 3:��Ҫ����TSU�ָ�¼��ӿ�, 4:��Ҫ����TSU��ͣ¼��ӿ� */
    } record_info_t;

    /* ¼����Ϣ���� */
    typedef struct _record_info_list_t
    {
        osip_list_t* pRecordInfoList;
#ifdef MULTI_THR
        osip_mutex_t* lock;
#endif
    } record_info_list_t;

    /* ������¼����Ϣ���� */
    typedef std::deque <record_info_t*> needtoproc_recordinfo_queue;

    /* ¼���¼�ṹ */
    typedef struct _VideoRecord
    {
        int DeviceIndex;
        int StorageIndex;
        int StartTime;
        int StopTime;
        int Size;
        string StorageIP;
        string StoragePath;
        int Type;
        int Resved1;
        string Resved2;
    } VideoRecord;

    /* ¼���¼���� */
    typedef std::vector<VideoRecord> VideoRecordList;
    typedef std::vector<VideoRecord>::iterator VideoRecordList_Iterator;

    extern int AddRecordInfo2DB(record_info_t * pRecordInfo, DBOper * pRecord_Srv_dboper);
    extern int add_record_info_by_message_cmd(unsigned int device_index, DBOper* pRecord_Srv_dboper);
    extern int check_plan_action_record_info_from_db_to_list(DBOper* pRecord_Srv_dboper);
    extern void check_RecordInfo_need_to_reload_begin(DBOper* pDboper);
    extern void check_RecordInfo_need_to_reload_end();
    extern void check_RecordTimeSchedConfig_need_to_reload(DBOper* pDboper);
    extern int check_record_info_from_db_to_list(DBOper* pRecord_Srv_dboper);
    extern int check_record_time_sched_config_from_db_to_list(record_time_sched_t * pRecordTimeSched, DBOper * pDBOper);
    extern int check_record_time_sched_from_db_to_list(DBOper * pDBOper);
    extern int check_shdb_alarm_upload_pic_record_info_from_db_to_list(DBOper* pRecord_Srv_dboper);
    extern int check_shdb_daily_upload_pic_record_info_from_db_to_list(DBOper* pRecord_Srv_dboper);
    extern int debug_record_info_list_lock(const char* file, int line, const char* func);
    extern int debug_record_info_list_unlock(const char* file, int line, const char* func);
    extern int debug_record_time_sched_list_lock(const char * file, int line, const char * func);
    extern int debug_record_time_sched_list_unlock(const char * file, int line, const char * func);
    extern int delete_record_info_from_list_by_mark();
    extern int delete_record_time_sched_from_list_by_mark();
    extern int delRecordInfo2DB(unsigned int device_index, DBOper * pRecord_Srv_dboper);
    extern int del_record_info_by_message_cmd(unsigned int device_index, DBOper* pRecord_Srv_dboper);
    extern int find_is_cr_index_used_by_other_record_info(int current_cr_index, int current_pos);
    extern int find_record_config_by_device_index(unsigned int uDeviceIndex, DBOper * pDboper);
    extern int get_record_cr_index_by_record_index(unsigned int uID);
    extern int get_record_info_index_from_list(vector<unsigned int>& RecordInfoIndexVector);
    extern int get_record_status_from_record_time_config(osip_list_t * pDayOfWeekTimeList);
    extern int has_record_info_find_by_stream_type(unsigned int device_index, int stream_type, int record_type);
    extern int RecordInfo_db_refresh_proc();
    extern int RecordTimeSchedConfigProc(record_time_sched_t * pRecordTimeSched);
    extern int RecordTimeSchedConfig_db_refresh_proc();
    extern int record_info_add(record_info_t* pRecordInfo);
    extern int record_info_find_by_cr_index(int cr_index);
    extern int record_info_find_by_cr_index_for_response(int cr_index);
    extern int record_info_find_by_stream_type(unsigned int device_index, int stream_type);
    extern int record_info_find_by_stream_type2(unsigned int device_index, int stream_type);
    extern void record_info_free(record_info_t* record_info);
    extern record_info_t* record_info_get(int pos);
    extern record_info_t* record_info_get_by_record_index(unsigned int index);
    extern record_info_t* record_info_get_by_record_type(unsigned int device_index, int record_type);
    extern record_info_t* record_info_get_by_record_type2(unsigned int device_index, int record_type);
    extern record_info_t* record_info_get_by_stream_type_and_record_type(unsigned int device_index, int stream_type, int record_type);
    extern record_info_t* record_info_get_by_stream_type_and_record_type2(unsigned int device_index, int stream_type, int record_type);
    extern int record_info_init(record_info_t** record_info);
    extern void record_info_list_free();
    extern int record_info_list_init();
    extern int record_info_list_lock();
    extern int record_info_list_unlock();
    extern int record_info_remove(int pos);
    extern int record_time_config_add(osip_list_t * pDayOfWeekTimeList, unsigned int uID, int iBeginTime, int iEndTime);
    extern void record_time_config_free(record_time_config_t * time_config);
    extern record_time_config_t* record_time_config_get(osip_list_t * pDayOfWeekTimeList, unsigned int uID);
    extern int record_time_config_init(record_time_config_t** time_config);
    extern int record_time_sched_add(unsigned int uID, int record_cr_index);
    extern void record_time_sched_free(record_time_sched_t * record_time_sched);
    extern record_time_sched_t* record_time_sched_get(unsigned int uID);
    extern int record_time_sched_init(record_time_sched_t** record_time_sched);
    extern void record_time_sched_list_free();
    extern int record_time_sched_list_init();
    extern int record_time_sched_list_lock();
    extern int record_time_sched_list_unlock();
    extern int RemoveDeviceRecordInfo(char * device_id, int stream_type, int tsu_resource_index);
    extern int RemoveRecordTimeSchedConfig(record_time_sched_t * pRecordTimeSched);
    extern int RemoveRecordTimeSchedMark(unsigned int uID);
    extern void scan_record_info_list();
    extern void scan_record_info_list_for_monitor_print();
    extern void scan_record_time_sched_list();
    extern int set_record_info_list_del_mark(int del_mark);
    extern int set_record_time_sched_list_del_mark(int del_mark);
    extern void ShowRecordInfo(int sock, int type);
    extern void ShowRecordTimeSchedInfo(int sock);

#ifdef ENABLE_DEBUG_LOCK
#define RECORD_INFO_SMUTEX_LOCK() debug_record_info_list_lock(__FILE__, __LINE__, __func__)
#define RECORD_INFO_SMUTEX_UNLOCK() debug_record_info_list_unlock(__FILE__, __LINE__, __func__)
#define RECORD_TIME_SCHED_SMUTEX_LOCK() debug_record_time_sched_list_lock(__FILE__, __LINE__, __func__)
#define RECORD_TIME_SCHED_SMUTEX_UNLOCK() debug_record_time_sched_list_unlock(__FILE__, __LINE__, __func__)
#else
#define RECORD_INFO_SMUTEX_LOCK() record_info_list_lock()
#define RECORD_INFO_SMUTEX_UNLOCK() record_info_list_unlock()
#define RECORD_TIME_SCHED_SMUTEX_LOCK() record_time_sched_list_lock()
#define RECORD_TIME_SCHED_SMUTEX_UNLOCK() record_time_sched_list_unlock()
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __UDP_TL_H__ */