#include <jni.h>
#include <string>
#include <fstream>
#include <sstream>

extern "C"
JNIEXPORT jint JNICALL
Java_net_nctucs_lapsap_root_1detection_11_MainActivity_isRooted(JNIEnv *env, jobject object_main) {

    // busybox method
    FILE* pipe = popen("busybox", "r");
    char buffer[128];
    std::string resultCmd = "";
    if(fgets(buffer, 128, pipe) != NULL)
        resultCmd = buffer;
    pclose(pipe);
    if(resultCmd != "")
        return true;
    // which su method
    pipe = popen("which su", "r");
    resultCmd = "";
    if(fgets(buffer, 128, pipe) != NULL)
        resultCmd = buffer;
    pclose(pipe);
    if(resultCmd != "")
        return true;
    // package manager method
    resultCmd = "";
    pipe = popen("pm list packages | grep supersu", "r");
    while(!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL)
            resultCmd += buffer;
    }
    pclose(pipe);
    if(resultCmd != "")
        return true;

    // build tag method text = android.os.Build.TAGS;
    jclass class_build = env->FindClass("android/os/Build");
    jfieldID field_build = env->GetStaticFieldID(class_build, "TAGS", "Ljava/lang/String;");
    jstring jstring_build = (jstring) env->GetStaticObjectField(class_build, field_build);
    std::string string_build = env->GetStringUTFChars(jstring_build, 0);
    if( string_build != "release-keys" )
        return true;

    // path method
    const std::string paths[] ={"/system/app/Superuser.apk", "/sbin/su", "/system/bin/su", "/system/xbin/su", "/data/local/xbin/su",
                                "/data/local/bin/su", "/system/sd/xbin/su", "/system/bin/failsafe/su", "/data/local/su", "/su/bin/su"};
    int siz = sizeof(paths) / sizeof(paths[0]) ;
    for(int i=0; i<siz; i++){
        if(FILE *file = fopen(paths[i].c_str(), "r")) {
            fclose(file);
            return true;
        }
    }

    return false;
}
