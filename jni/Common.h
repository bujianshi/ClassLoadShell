/*
 * Common.h
 *
 *  Created on: 2016��1��14��
 *      Author: peng
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <android/log.h>
#define DEBUG 1
#define LOG_TAG "tomagoyaky_native"

#if DEBUG
#define LOGD(fmt,...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "[%s]" fmt, __FUNCTION__,##__VA_ARGS__)
#define LOGI(fmt,...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "[%s]" fmt, __FUNCTION__,##__VA_ARGS__)
#define LOGV(fmt,...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "[%s]" fmt, __FUNCTION__,##__VA_ARGS__)
#define LOGW(fmt,...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, "[%s]" fmt, __FUNCTION__,##__VA_ARGS__)
#define LOGE(fmt,...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "[%s]" fmt, __FUNCTION__,##__VA_ARGS__)
#define LOGF(fmt,...) __android_log_print(ANDROID_LOG_FATAL, LOG_TAG, "[%s]" fmt, __FUNCTION__,##__VA_ARGS__)
#else
#define LOGD(...) while(0){}
#define LOGI(...) while(0){}
#define LOGV(...) while(0){}
#define LOGW(...) while(0){}
#define LOGE(...) while(0){}
#define LOGW(...) while(0){}
#endif

char* Jstring2CStr(JNIEnv* env, jstring jstr, int* charLen) {
	char* rtn = NULL;
	jclass clsstring = env->FindClass("java/lang/String");
	jstring strencode = env->NewStringUTF("UTF-8");

	jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
	jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
	jsize alen = env->GetArrayLength(barr);
	*charLen = alen + 1;
	jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
	if (alen > 0) {
		rtn = (char*) malloc(alen + 1);
		memcpy(rtn, ba, alen);
		rtn[alen] = 0;
	}
	env->ReleaseByteArrayElements(barr, ba, 0);
	return rtn;
}
jstring CStr2Jstring(JNIEnv* env, const char* pat) {
	//����java String�� strClass
	jclass strClass = (env)->FindClass("Ljava/lang/String;");
	//��ȡjava String�෽��String(byte[],String)�Ĺ�����,���ڽ�����byte[]����ת��Ϊһ����String
	jmethodID ctorID = (env)->GetMethodID(strClass, "<init>",
			"([BLjava/lang/String;)V");
	//����byte����
	jbyteArray bytes = (env)->NewByteArray((jsize) strlen(pat));
	//��char* ת��Ϊbyte����
	(env)->SetByteArrayRegion(bytes, 0, (jsize) strlen(pat), (jbyte*) pat);
	//����String, ������������,����byte����ת����Stringʱ�Ĳ���
	jstring encoding = (env)->NewStringUTF("UTF-8");
	//��byte����ת��Ϊjava String,�����
	return (jstring) (env)->NewObject(strClass, ctorID, bytes, "UTF-8");
}

#endif /* COMMON_H_ */
