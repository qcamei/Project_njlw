#!/bin/sh
#------------------------------------------------------------main--------------------------------------------
cd /data

echo "#####ִ���ֻ�MMS�����������ݿⱸ�ݽű�:��ʼ#####"

echo "*******************************************************************"

echo "һ.ɾ���ֻ�MMSԴ���ݿ��еĴ�����:��ʼ---"

source /app/Delete_trig_mobile.sh

echo "һ.ɾ���ֻ�MMSԴ���ݿ��еĴ�����:����---"

echo "*******************************************************************"

echo "��.ִ���ֻ�MMS�������ݿ�����:��ʼ---"

mysqldump -uroot -pwiscom --host=$1 --opt EV9000DB_MOBILE | mysql -uroot -pwiscom --host=$2 -C EV9000DB_MOBILE
mysqldump -uroot -pwiscom --host=$1 --opt app_server_db | mysql -uroot -pwiscom --host=$2 -C app_server_db

echo "��.ִ���ֻ�MMS�������ݿ�����:����---"

echo "*******************************************************************"

echo "��.�ָ��ֻ�MMSԴ���ݿ��еĴ�����:��ʼ---"

source /app/Create_trig_mobile.sh

echo "��.�ָ��ֻ�MMSԴ���ݿ��еĴ�����:����---"

echo "*******************************************************************"

echo "#####ִ���ֻ�MMS�����������ݿⱸ�ݽű�:����#####"