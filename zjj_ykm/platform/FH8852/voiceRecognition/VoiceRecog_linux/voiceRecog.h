#ifdef VOICE_RECOG_DLL
#define VOICERECOGNIZEDLL_API __declspec(dllexport)
#else
#define VOICERECOGNIZEDLL_API
#endif


#ifndef VOICE_RECOG_H
#define VOICE_RECOG_H

#ifdef __cplusplus
extern "C" {
#endif
	enum VRErrorCode
	{
		VR_SUCCESS = 0, VR_NoSignal = -1, VR_ECCError = -2, VR_NotEnoughSignal = 100
		, VR_NotHeaderOrTail = 101, VR_RecogCountZero = 102
	};

	enum DecoderPriority
	{
		CPUUsePriority = 1//��ռ�ڴ棬��CPU���ıȽϴ�һЩ
		, MemoryUsePriority = 2//��ռCPU�����ڴ����Ĵ�һЩ
		, CryDetectPriority = 3
	};

	typedef enum {vr_false = 0, vr_true = 1} vr_bool;

	typedef void (*vr_pRecognizerStartListener)(void *_listener, float _soundTime);
	//_result���ΪVR_SUCCESS�����ʾʶ��ɹ�������Ϊ�����룬�ɹ��Ļ�_data��������
	typedef void (*vr_pRecognizerEndListener)(void *_listener, float _soundTime, int _result, char *_data, int _dataLen);
	struct VoiceMatch
	{
		short frequency;
		short length;
		float strength;

#ifdef _DEBUG
		////debug
		//short frequencyY;
		//char bigMatchCount, preciseMatchCount;
#endif
	};
	typedef void (*vr_pRecognizerMatchListener)(void *_listener, int _timeIdx, struct VoiceMatch *_matches, int _matchesLen);

	//��������ʶ����
	VOICERECOGNIZEDLL_API void *vr_createVoiceRecognizer(enum DecoderPriority _decoderPriority);
	VOICERECOGNIZEDLL_API void *vr_createVoiceRecognizer2(enum DecoderPriority _decoderPriority, int _sampleRate);

	//����ʶ����
	VOICERECOGNIZEDLL_API void vr_destroyVoiceRecognizer(void *_recognizer);

	//���ý���Ƶ��
	//_freqs�����Ǿ�̬�ģ�������������в����ͷ�
	VOICERECOGNIZEDLL_API void vr_setRecognizeFreqs(void *_recognizer, int *_freqs, int _freqCount);
	//���õڶ���Ƶ�ε�Ƶ��
	VOICERECOGNIZEDLL_API void vr_setRecognizeFreqs2(void *_recognizer, int *_freqs, int _freqCount);

	//����ʶ���źŵļ�����
	VOICERECOGNIZEDLL_API void vr_setRecognizerListener(void *_recognizer, void *_listener, vr_pRecognizerStartListener _startListener, vr_pRecognizerEndListener _endListener);
	VOICERECOGNIZEDLL_API void vr_setRecognizerListener2(void *_recognizer, void *_listener, vr_pRecognizerStartListener _startListener, 
		vr_pRecognizerEndListener _endListener, vr_pRecognizerMatchListener _matchListener);
	//���õڶ���Ƶ�εļ�����
	VOICERECOGNIZEDLL_API void vr_setRecognizerFreq2Listener(void *_recognizer, void *_listener, vr_pRecognizerStartListener _startListener, 
		vr_pRecognizerEndListener _endListener, vr_pRecognizerMatchListener _matchListener);

	//��ʼʶ��
	//����һ�����̣߳����������ֹͣʶ��֮ǰ���᷵��
	VOICERECOGNIZEDLL_API void vr_runRecognizer(void *_recognizer);

	//��ͣ�źŷ���
	VOICERECOGNIZEDLL_API void vr_pauseRecognize(void *_recognizer, int _microSeconds);

	//ֹͣʶ�𣬸ú������ú�vr_runRecognizer�᷵��
	//�ú���ֻ����ʶ���̷߳����˳��źţ��ж�ʶ�����Ƿ������Ѿ��˳�Ҫʹ�����µ�vr_isRecognizerStopped����
	VOICERECOGNIZEDLL_API void vr_stopRecognize(void *_recognizer);

	//�ж�ʶ�����߳��Ƿ��Ѿ��˳�
	VOICERECOGNIZEDLL_API vr_bool vr_isRecognizerStopped(void *_recognizer);

	//Ҫ����������Ҫ��Ϊ44100����������16bits�������ȣ�С�˱������Ƶ����
	//С�˱��벻���ر���һ����¼�������ݶ���С�˱����
	VOICERECOGNIZEDLL_API int vr_writeData(void *_recognizer, char *_data, int _dataLen);	

	VOICERECOGNIZEDLL_API int vr_getVer();

#if 0
	//��voiceRecognizer��ȡ���_seconds�������voicePattern�����صĶ���Ҫʹ���߸���ɾ��
	VOICERECOGNIZEDLL_API void *vr_getVoicePattern(void *_recognizer, int _seconds);
	//��voicePatternת��base64�������ϴ������أ����ص��ַ���Ҫʹ���߸����ͷ�
	VOICERECOGNIZEDLL_API char *vr_voicePatternToBase64(void *_pattern);
	//��base64�����voicePattern��ԭ���ڴ���󣬷��ص��ַ���Ҫʹ���߸���ɾ��
	VOICERECOGNIZEDLL_API void *vr_base64ToVoicePattern(char *_base64);
	//ɾ��voicePattern�ڴ�
	VOICERECOGNIZEDLL_API void vr_destoryVoicePattern(void *_pattern);

	VOICERECOGNIZEDLL_API void *vr_createVoicePatternMatcher();
	VOICERECOGNIZEDLL_API void vr_destoryVoicePatternMatcher(void *_matcher);
	//��voiceRecognizer��voiceMatcher����������ʹvoiceRecognizer������voicePattern�Զ�����voiceMatcher
	//_streamID�����·��Ƶ���ı�ţ���vr_matchVoicePattern���ص���Ƶ��������streamID�����
	VOICERECOGNIZEDLL_API void vr_addVoicePatternSource(void *_matcher, short _streamID, void *_sourceRecognizer);
	//�ֶ���ĳһ��voicePattern����voiceMatcher
	//_streamID������ͬ��
	VOICERECOGNIZEDLL_API void vr_addVoicePattern(void *_matcher, short _streamID, void *_pattern);
	//���ض��ƥ��̶Ȳ�ͬ��������ͬ������_streamIDResult�������
	//_matchResultΪÿһ·��ƥ��İٷֱ�
	//�����Ƿ�ɹ�ƥ��
	VOICERECOGNIZEDLL_API int vr_matchVoicePattern(void *_matcher, void *_pattern, short *_streamIDResult, int *_matchResult, int _resultBufLen, int *_returnLen);
#endif


	//Ӧ�ò����ӿ�

	//int vr_decodeData(char *_hexs, int _hexsLen, int *_hexsCostLen, char *_result, int _resultLen);
	
	VOICERECOGNIZEDLL_API vr_bool vr_decodeString(int _recogStatus, char *_data, int _dataLen, char *_result, int _resultLen);

	//��������������ͱ�־
	enum InfoType
	{
		IT_WIFI = 0//˵�����������ΪWiFi
		, IT_SSID_WIFI = 1//ssid�����WIFI
		, IT_PHONE = 2//˵�����������Ϊ�ֻ�ע����Ϣ
		, IT_STRING = 3//�����ַ���
		, IT_BLOCKS = 7
	};

	VOICERECOGNIZEDLL_API enum InfoType vr_decodeInfoType(char *_data, int _dataLen);

	//wifi����
	struct WiFiInfo
	{
		char mac[8];
		int macLen;
		char pwd[80];
		int pwdLen;
	};

	VOICERECOGNIZEDLL_API vr_bool vr_decodeWiFi(int _result, char *_data, int _dataLen, struct WiFiInfo *_wifi);

	struct SSIDWiFiInfo
	{
		char ssid[33];
		int ssidLen;
		char pwd[80];
		int pwdLen;
	};

	VOICERECOGNIZEDLL_API vr_bool vr_decodeSSIDWiFi(int _result, char *_data, int _dataLen, struct SSIDWiFiInfo *_wifi);


	struct ZS_SSIDWiFiInfo
	{
		char phone[12];
		char ssid[33];
		int ssidLen;
		char pwd[80];
		int pwdLen;
	};

	VOICERECOGNIZEDLL_API vr_bool vr_decodeZSSSIDWiFi(int _result, char *_data, int _dataLen, struct ZS_SSIDWiFiInfo *_wifi);

	struct BlocksComposer
	{
		short blockCount;
		short dataLen;
		char blockFlags[4];
		char data[512];
	};
	VOICERECOGNIZEDLL_API void vr_bs_reset(struct BlocksComposer *_this);
	VOICERECOGNIZEDLL_API int vr_bs_composeBlock(struct BlocksComposer *_this, char *_blockData, int _blockDataLen);
	VOICERECOGNIZEDLL_API vr_bool vr_bs_isAllBlockComposed(struct BlocksComposer *_this);


#ifdef __cplusplus
}
#endif

#endif


