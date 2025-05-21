
#include <string>
#include <cstdint>
#include "bios.h"
#include <jni.h>

using std::string;


class BackupManager {

protected:
  BackupManager();
public:  
  static BackupManager * instance_;
  static BackupManager * getInstance(){
    if( instance_==NULL ) instance_ = new BackupManager();
    return instance_; 
  }

  virtual ~BackupManager();
  int getDevicelist( string & jsonstr );
  int getFilelist( int deviceid, string & jsonstr );
  int deletefile( int index );
  int getFile( int index, string & jsonstr );
  int putFile( const string & jsonstr );
  int copy( int target_device, int file_index );

protected:  
  uint32_t currentbupdevice_ = 0;
  deviceinfo_struct* devices_ = NULL;
  int32_t numbupdevices_ = 0;
  int32_t current_device_ = -1;
  saveinfo_struct* saves_ = NULL;
  int32_t numsaves_ = 0;

};

jstring NewStringMS932(JNIEnv *env, const char *sjis);

extern "C"{

JNIEXPORT jstring JNICALL Java_org_uoyabause_android_YabauseRunnable_getDevicelist(JNIEnv* env) {
  BackupManager * i = BackupManager::getInstance();
  string jsonstr;
  i->getDevicelist(jsonstr);
  return env->NewStringUTF(jsonstr.c_str());
}

JNIEXPORT jstring JNICALL Java_org_uoyabause_android_YabauseRunnable_getFilelist(JNIEnv* env, jobject obj, jint deviceid ) {
  BackupManager * i = BackupManager::getInstance();
  string jsonstr;
  i->getFilelist(deviceid,jsonstr);
  return env->NewStringUTF(jsonstr.c_str());
}

JNIEXPORT jint JNICALL Java_org_uoyabause_android_YabauseRunnable_deletefile(JNIEnv* env, jobject obj, jint index ) {
  BackupManager * i = BackupManager::getInstance();
  string jsonstr;
  return i->deletefile(index);
}

JNIEXPORT jstring JNICALL Java_org_uoyabause_android_YabauseRunnable_getFile(JNIEnv* env, jobject obj, jint index  ) {
  BackupManager * i = BackupManager::getInstance();
  string jsonstr;
  i->getFile(index,jsonstr);
  return env->NewStringUTF(jsonstr.c_str());
}

JNIEXPORT jint JNICALL Java_org_uoyabause_android_YabauseRunnable_putFile(JNIEnv* env, jobject obj, jstring jsonstr  ) {
  BackupManager * i = BackupManager::getInstance();
  jboolean dummy;
  const char *cpath = env->GetStringUTFChars( jsonstr, &dummy);
  int rtn = i->putFile(string(cpath));
  env->ReleaseStringUTFChars( jsonstr, cpath);
  return rtn;
}

JNIEXPORT jint JNICALL Java_org_uoyabause_android_YabauseRunnable_copy(JNIEnv* env, jobject obj, jint target, jint file  ) {
  BackupManager * i = BackupManager::getInstance();
  return i->copy(target,file);
}


}