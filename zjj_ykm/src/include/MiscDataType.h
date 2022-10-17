





#ifndef __MISC_DATA_TYPE_H__
#define __MISC_DATA_TYPE_H__



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */


#include <stdint.h>
#include <time.h>
#include <sys/time.h>




/**
 * Identify the syntax and semantics of the bitstream.
 * The principle is roughly:
 * Two decoders with the same ID can decode the same streams.
 * Two encoders with the same ID can encode compatible streams.
 * There may be slight deviations from the principle due to implementation
 * details.
 *
 * If you add a codec ID to this list, add it so that
 * 1. no value of a existing codec ID changes (that would break ABI),
 * 2. it is as close as possible to similar codecs
 *
 * After adding new codec IDs, do not forget to add an entry to the codec
 * descriptor list and bump libavcodec minor version.
 */
enum AVCodecID {
    AV_CODEC_ID_NONE,

    /* video codecs */
    AV_CODEC_ID_MPEG1VIDEO,
    AV_CODEC_ID_MPEG2VIDEO, ///< preferred ID for MPEG-1/2 video decoding
#if FF_API_XVMC
    AV_CODEC_ID_MPEG2VIDEO_XVMC,
#endif /* FF_API_XVMC */
    AV_CODEC_ID_H261,
    AV_CODEC_ID_H263,
    AV_CODEC_ID_RV10,
    AV_CODEC_ID_RV20,
    AV_CODEC_ID_MJPEG,
    AV_CODEC_ID_MJPEGB,
    AV_CODEC_ID_LJPEG,
    AV_CODEC_ID_SP5X,
    AV_CODEC_ID_JPEGLS,
    AV_CODEC_ID_MPEG4,
    AV_CODEC_ID_RAWVIDEO,
    AV_CODEC_ID_MSMPEG4V1,
    AV_CODEC_ID_MSMPEG4V2,
    AV_CODEC_ID_MSMPEG4V3,
    AV_CODEC_ID_WMV1,
    AV_CODEC_ID_WMV2,
    AV_CODEC_ID_H263P,
    AV_CODEC_ID_H263I,
    AV_CODEC_ID_FLV1,
    AV_CODEC_ID_SVQ1,
    AV_CODEC_ID_SVQ3,
    AV_CODEC_ID_DVVIDEO,
    AV_CODEC_ID_HUFFYUV,
    AV_CODEC_ID_CYUV,
    AV_CODEC_ID_H264,
    AV_CODEC_ID_INDEO3,
    AV_CODEC_ID_VP3,
    AV_CODEC_ID_THEORA,
    AV_CODEC_ID_ASV1,
    AV_CODEC_ID_ASV2,
    AV_CODEC_ID_FFV1,
    AV_CODEC_ID_4XM,
    AV_CODEC_ID_VCR1,
    AV_CODEC_ID_CLJR,
    AV_CODEC_ID_MDEC,
    AV_CODEC_ID_ROQ,
    AV_CODEC_ID_INTERPLAY_VIDEO,
    AV_CODEC_ID_XAN_WC3,
    AV_CODEC_ID_XAN_WC4,
    AV_CODEC_ID_RPZA,
    AV_CODEC_ID_CINEPAK,
    AV_CODEC_ID_WS_VQA,
    AV_CODEC_ID_MSRLE,
    AV_CODEC_ID_MSVIDEO1,
    AV_CODEC_ID_IDCIN,
    AV_CODEC_ID_8BPS,
    AV_CODEC_ID_SMC,
    AV_CODEC_ID_FLIC,
    AV_CODEC_ID_TRUEMOTION1,
    AV_CODEC_ID_VMDVIDEO,
    AV_CODEC_ID_MSZH,
    AV_CODEC_ID_ZLIB,
    AV_CODEC_ID_QTRLE,
    AV_CODEC_ID_TSCC,
    AV_CODEC_ID_ULTI,
    AV_CODEC_ID_QDRAW,
    AV_CODEC_ID_VIXL,
    AV_CODEC_ID_QPEG,
    AV_CODEC_ID_PNG,
    AV_CODEC_ID_PPM,
    AV_CODEC_ID_PBM,
    AV_CODEC_ID_PGM,
    AV_CODEC_ID_PGMYUV,
    AV_CODEC_ID_PAM,
    AV_CODEC_ID_FFVHUFF,
    AV_CODEC_ID_RV30,
    AV_CODEC_ID_RV40,
    AV_CODEC_ID_VC1,
    AV_CODEC_ID_WMV3,
    AV_CODEC_ID_LOCO,
    AV_CODEC_ID_WNV1,
    AV_CODEC_ID_AASC,
    AV_CODEC_ID_INDEO2,
    AV_CODEC_ID_FRAPS,
    AV_CODEC_ID_TRUEMOTION2,
    AV_CODEC_ID_BMP,
    AV_CODEC_ID_CSCD,
    AV_CODEC_ID_MMVIDEO,
    AV_CODEC_ID_ZMBV,
    AV_CODEC_ID_AVS,
    AV_CODEC_ID_SMACKVIDEO,
    AV_CODEC_ID_NUV,
    AV_CODEC_ID_KMVC,
    AV_CODEC_ID_FLASHSV,
    AV_CODEC_ID_CAVS,
    AV_CODEC_ID_JPEG2000,
    AV_CODEC_ID_VMNC,
    AV_CODEC_ID_VP5,
    AV_CODEC_ID_VP6,
    AV_CODEC_ID_VP6F,
    AV_CODEC_ID_TARGA,
    AV_CODEC_ID_DSICINVIDEO,
    AV_CODEC_ID_TIERTEXSEQVIDEO,
    AV_CODEC_ID_TIFF,
    AV_CODEC_ID_GIF,
    AV_CODEC_ID_DXA,
    AV_CODEC_ID_DNXHD,
    AV_CODEC_ID_THP,
    AV_CODEC_ID_SGI,
    AV_CODEC_ID_C93,
    AV_CODEC_ID_BETHSOFTVID,
    AV_CODEC_ID_PTX,
    AV_CODEC_ID_TXD,
    AV_CODEC_ID_VP6A,
    AV_CODEC_ID_AMV,
    AV_CODEC_ID_VB,
    AV_CODEC_ID_PCX,
    AV_CODEC_ID_SUNRAST,
    AV_CODEC_ID_INDEO4,
    AV_CODEC_ID_INDEO5,
    AV_CODEC_ID_MIMIC,
    AV_CODEC_ID_RL2,
    AV_CODEC_ID_ESCAPE124,
    AV_CODEC_ID_DIRAC,
    AV_CODEC_ID_BFI,
    AV_CODEC_ID_CMV,
    AV_CODEC_ID_MOTIONPIXELS,
    AV_CODEC_ID_TGV,
    AV_CODEC_ID_TGQ,
    AV_CODEC_ID_TQI,
    AV_CODEC_ID_AURA,
    AV_CODEC_ID_AURA2,
    AV_CODEC_ID_V210X,
    AV_CODEC_ID_TMV,
    AV_CODEC_ID_V210,
    AV_CODEC_ID_DPX,
    AV_CODEC_ID_MAD,
    AV_CODEC_ID_FRWU,
    AV_CODEC_ID_FLASHSV2,
    AV_CODEC_ID_CDGRAPHICS,
    AV_CODEC_ID_R210,
    AV_CODEC_ID_ANM,
    AV_CODEC_ID_BINKVIDEO,
    AV_CODEC_ID_IFF_ILBM,
#define AV_CODEC_ID_IFF_BYTERUN1 AV_CODEC_ID_IFF_ILBM
    AV_CODEC_ID_KGV1,
    AV_CODEC_ID_YOP,
    AV_CODEC_ID_VP8,
    AV_CODEC_ID_PICTOR,
    AV_CODEC_ID_ANSI,
    AV_CODEC_ID_A64_MULTI,
    AV_CODEC_ID_A64_MULTI5,
    AV_CODEC_ID_R10K,
    AV_CODEC_ID_MXPEG,
    AV_CODEC_ID_LAGARITH,
    AV_CODEC_ID_PRORES,
    AV_CODEC_ID_JV,
    AV_CODEC_ID_DFA,
    AV_CODEC_ID_WMV3IMAGE,
    AV_CODEC_ID_VC1IMAGE,
    AV_CODEC_ID_UTVIDEO,
    AV_CODEC_ID_BMV_VIDEO,
    AV_CODEC_ID_VBLE,
    AV_CODEC_ID_DXTORY,
    AV_CODEC_ID_V410,
    AV_CODEC_ID_XWD,
    AV_CODEC_ID_CDXL,
    AV_CODEC_ID_XBM,
    AV_CODEC_ID_ZEROCODEC,
    AV_CODEC_ID_MSS1,
    AV_CODEC_ID_MSA1,
    AV_CODEC_ID_TSCC2,
    AV_CODEC_ID_MTS2,
    AV_CODEC_ID_CLLC,
    AV_CODEC_ID_MSS2,
    AV_CODEC_ID_VP9,
    AV_CODEC_ID_AIC,
    AV_CODEC_ID_ESCAPE130,
    AV_CODEC_ID_G2M,
    AV_CODEC_ID_WEBP,
    AV_CODEC_ID_HNM4_VIDEO,
    AV_CODEC_ID_HEVC,
#define AV_CODEC_ID_H265 AV_CODEC_ID_HEVC
    AV_CODEC_ID_FIC,
    AV_CODEC_ID_ALIAS_PIX,
    AV_CODEC_ID_BRENDER_PIX,
    AV_CODEC_ID_PAF_VIDEO,
    AV_CODEC_ID_EXR,
    AV_CODEC_ID_VP7,
    AV_CODEC_ID_SANM,
    AV_CODEC_ID_SGIRLE,
    AV_CODEC_ID_MVC1,
    AV_CODEC_ID_MVC2,
    AV_CODEC_ID_HQX,
    AV_CODEC_ID_TDSC,
    AV_CODEC_ID_HQ_HQA,
    AV_CODEC_ID_HAP,
    AV_CODEC_ID_DDS,
    AV_CODEC_ID_DXV,
    AV_CODEC_ID_SCREENPRESSO,
    AV_CODEC_ID_RSCC,

    AV_CODEC_ID_Y41P = 0x8000,
    AV_CODEC_ID_AVRP,
    AV_CODEC_ID_012V,
    AV_CODEC_ID_AVUI,
    AV_CODEC_ID_AYUV,
    AV_CODEC_ID_TARGA_Y216,
    AV_CODEC_ID_V308,
    AV_CODEC_ID_V408,
    AV_CODEC_ID_YUV4,
    AV_CODEC_ID_AVRN,
    AV_CODEC_ID_CPIA,
    AV_CODEC_ID_XFACE,
    AV_CODEC_ID_SNOW,
    AV_CODEC_ID_SMVJPEG,
    AV_CODEC_ID_APNG,
    AV_CODEC_ID_DAALA,
    AV_CODEC_ID_CFHD,

    /* various PCM "codecs" */
    AV_CODEC_ID_FIRST_AUDIO = 0x10000,     ///< A dummy id pointing at the start of audio codecs
    AV_CODEC_ID_PCM_S16LE = 0x10000,
    AV_CODEC_ID_PCM_S16BE,
    AV_CODEC_ID_PCM_U16LE,
    AV_CODEC_ID_PCM_U16BE,
    AV_CODEC_ID_PCM_S8,
    AV_CODEC_ID_PCM_U8,
    AV_CODEC_ID_PCM_MULAW,
    AV_CODEC_ID_PCM_ALAW,
    AV_CODEC_ID_PCM_S32LE,
    AV_CODEC_ID_PCM_S32BE,
    AV_CODEC_ID_PCM_U32LE,
    AV_CODEC_ID_PCM_U32BE,
    AV_CODEC_ID_PCM_S24LE,
    AV_CODEC_ID_PCM_S24BE,
    AV_CODEC_ID_PCM_U24LE,
    AV_CODEC_ID_PCM_U24BE,
    AV_CODEC_ID_PCM_S24DAUD,
    AV_CODEC_ID_PCM_ZORK,
    AV_CODEC_ID_PCM_S16LE_PLANAR,
    AV_CODEC_ID_PCM_DVD,
    AV_CODEC_ID_PCM_F32BE,
    AV_CODEC_ID_PCM_F32LE,
    AV_CODEC_ID_PCM_F64BE,
    AV_CODEC_ID_PCM_F64LE,
    AV_CODEC_ID_PCM_BLURAY,
    AV_CODEC_ID_PCM_LXF,
    AV_CODEC_ID_S302M,
    AV_CODEC_ID_PCM_S8_PLANAR,
    AV_CODEC_ID_PCM_S24LE_PLANAR,
    AV_CODEC_ID_PCM_S32LE_PLANAR,
    AV_CODEC_ID_PCM_S16BE_PLANAR,
    /* new PCM "codecs" should be added right below this line starting with
     * an explicit value of for example 0x10800
     */

    /* various ADPCM codecs */
    AV_CODEC_ID_ADPCM_IMA_QT = 0x11000,
    AV_CODEC_ID_ADPCM_IMA_WAV,
    AV_CODEC_ID_ADPCM_IMA_DK3,
    AV_CODEC_ID_ADPCM_IMA_DK4,
    AV_CODEC_ID_ADPCM_IMA_WS,
    AV_CODEC_ID_ADPCM_IMA_SMJPEG,
    AV_CODEC_ID_ADPCM_MS,
    AV_CODEC_ID_ADPCM_4XM,
    AV_CODEC_ID_ADPCM_XA,
    AV_CODEC_ID_ADPCM_ADX,
    AV_CODEC_ID_ADPCM_EA,
    AV_CODEC_ID_ADPCM_G726,
    AV_CODEC_ID_ADPCM_CT,
    AV_CODEC_ID_ADPCM_SWF,
    AV_CODEC_ID_ADPCM_YAMAHA,
    AV_CODEC_ID_ADPCM_SBPRO_4,
    AV_CODEC_ID_ADPCM_SBPRO_3,
    AV_CODEC_ID_ADPCM_SBPRO_2,
    AV_CODEC_ID_ADPCM_THP,
    AV_CODEC_ID_ADPCM_IMA_AMV,
    AV_CODEC_ID_ADPCM_EA_R1,
    AV_CODEC_ID_ADPCM_EA_R3,
    AV_CODEC_ID_ADPCM_EA_R2,
    AV_CODEC_ID_ADPCM_IMA_EA_SEAD,
    AV_CODEC_ID_ADPCM_IMA_EA_EACS,
    AV_CODEC_ID_ADPCM_EA_XAS,
    AV_CODEC_ID_ADPCM_EA_MAXIS_XA,
    AV_CODEC_ID_ADPCM_IMA_ISS,
    AV_CODEC_ID_ADPCM_G722,
    AV_CODEC_ID_ADPCM_IMA_APC,
    AV_CODEC_ID_ADPCM_VIMA,
#if FF_API_VIMA_DECODER
    AV_CODEC_ID_VIMA = AV_CODEC_ID_ADPCM_VIMA,
#endif

    AV_CODEC_ID_ADPCM_AFC = 0x11800,
    AV_CODEC_ID_ADPCM_IMA_OKI,
    AV_CODEC_ID_ADPCM_DTK,
    AV_CODEC_ID_ADPCM_IMA_RAD,
    AV_CODEC_ID_ADPCM_G726LE,
    AV_CODEC_ID_ADPCM_THP_LE,
    AV_CODEC_ID_ADPCM_PSX,
    AV_CODEC_ID_ADPCM_AICA,

    /* AMR */
    AV_CODEC_ID_AMR_NB = 0x12000,
    AV_CODEC_ID_AMR_WB,

    /* RealAudio codecs*/
    AV_CODEC_ID_RA_144 = 0x13000,
    AV_CODEC_ID_RA_288,

    /* various DPCM codecs */
    AV_CODEC_ID_ROQ_DPCM = 0x14000,
    AV_CODEC_ID_INTERPLAY_DPCM,
    AV_CODEC_ID_XAN_DPCM,
    AV_CODEC_ID_SOL_DPCM,

    AV_CODEC_ID_SDX2_DPCM = 0x14800,

    /* audio codecs */
    AV_CODEC_ID_MP2 = 0x15000,
    AV_CODEC_ID_MP3, ///< preferred ID for decoding MPEG audio layer 1, 2 or 3
    AV_CODEC_ID_AAC,
    AV_CODEC_ID_AC3,
    AV_CODEC_ID_DTS,
    AV_CODEC_ID_VORBIS,
    AV_CODEC_ID_DVAUDIO,
    AV_CODEC_ID_WMAV1,
    AV_CODEC_ID_WMAV2,
    AV_CODEC_ID_MACE3,
    AV_CODEC_ID_MACE6,
    AV_CODEC_ID_VMDAUDIO,
    AV_CODEC_ID_FLAC,
    AV_CODEC_ID_MP3ADU,
    AV_CODEC_ID_MP3ON4,
    AV_CODEC_ID_SHORTEN,
    AV_CODEC_ID_ALAC,
    AV_CODEC_ID_WESTWOOD_SND1,
    AV_CODEC_ID_GSM, ///< as in Berlin toast format
    AV_CODEC_ID_QDM2,
    AV_CODEC_ID_COOK,
    AV_CODEC_ID_TRUESPEECH,
    AV_CODEC_ID_TTA,
    AV_CODEC_ID_SMACKAUDIO,
    AV_CODEC_ID_QCELP,
    AV_CODEC_ID_WAVPACK,
    AV_CODEC_ID_DSICINAUDIO,
    AV_CODEC_ID_IMC,
    AV_CODEC_ID_MUSEPACK7,
    AV_CODEC_ID_MLP,
    AV_CODEC_ID_GSM_MS, /* as found in WAV */
    AV_CODEC_ID_ATRAC3,
#if FF_API_VOXWARE
    AV_CODEC_ID_VOXWARE,
#endif
    AV_CODEC_ID_APE,
    AV_CODEC_ID_NELLYMOSER,
    AV_CODEC_ID_MUSEPACK8,
    AV_CODEC_ID_SPEEX,
    AV_CODEC_ID_WMAVOICE,
    AV_CODEC_ID_WMAPRO,
    AV_CODEC_ID_WMALOSSLESS,
    AV_CODEC_ID_ATRAC3P,
    AV_CODEC_ID_EAC3,
    AV_CODEC_ID_SIPR,
    AV_CODEC_ID_MP1,
    AV_CODEC_ID_TWINVQ,
    AV_CODEC_ID_TRUEHD,
    AV_CODEC_ID_MP4ALS,
    AV_CODEC_ID_ATRAC1,
    AV_CODEC_ID_BINKAUDIO_RDFT,
    AV_CODEC_ID_BINKAUDIO_DCT,
    AV_CODEC_ID_AAC_LATM,
    AV_CODEC_ID_QDMC,
    AV_CODEC_ID_CELT,
    AV_CODEC_ID_G723_1,
    AV_CODEC_ID_G729,
    AV_CODEC_ID_8SVX_EXP,
    AV_CODEC_ID_8SVX_FIB,
    AV_CODEC_ID_BMV_AUDIO,
    AV_CODEC_ID_RALF,
    AV_CODEC_ID_IAC,
    AV_CODEC_ID_ILBC,
    AV_CODEC_ID_OPUS,
    AV_CODEC_ID_COMFORT_NOISE,
    AV_CODEC_ID_TAK,
    AV_CODEC_ID_METASOUND,
    AV_CODEC_ID_PAF_AUDIO,
    AV_CODEC_ID_ON2AVC,
    AV_CODEC_ID_DSS_SP,

    AV_CODEC_ID_FFWAVESYNTH = 0x15800,
    AV_CODEC_ID_SONIC,
    AV_CODEC_ID_SONIC_LS,
    AV_CODEC_ID_EVRC,
    AV_CODEC_ID_SMV,
    AV_CODEC_ID_DSD_LSBF,
    AV_CODEC_ID_DSD_MSBF,
    AV_CODEC_ID_DSD_LSBF_PLANAR,
    AV_CODEC_ID_DSD_MSBF_PLANAR,
    AV_CODEC_ID_4GV,
    AV_CODEC_ID_INTERPLAY_ACM,
    AV_CODEC_ID_XMA1,
    AV_CODEC_ID_XMA2,

    /* subtitle codecs */
    AV_CODEC_ID_FIRST_SUBTITLE = 0x17000,          ///< A dummy ID pointing at the start of subtitle codecs.
    AV_CODEC_ID_DVD_SUBTITLE = 0x17000,
    AV_CODEC_ID_DVB_SUBTITLE,
    AV_CODEC_ID_TEXT,  ///< raw UTF-8 text
    AV_CODEC_ID_XSUB,
    AV_CODEC_ID_SSA,
    AV_CODEC_ID_MOV_TEXT,
    AV_CODEC_ID_HDMV_PGS_SUBTITLE,
    AV_CODEC_ID_DVB_TELETEXT,
    AV_CODEC_ID_SRT,

    AV_CODEC_ID_MICRODVD   = 0x17800,
    AV_CODEC_ID_EIA_608,
    AV_CODEC_ID_JACOSUB,
    AV_CODEC_ID_SAMI,
    AV_CODEC_ID_REALTEXT,
    AV_CODEC_ID_STL,
    AV_CODEC_ID_SUBVIEWER1,
    AV_CODEC_ID_SUBVIEWER,
    AV_CODEC_ID_SUBRIP,
    AV_CODEC_ID_WEBVTT,
    AV_CODEC_ID_MPL2,
    AV_CODEC_ID_VPLAYER,
    AV_CODEC_ID_PJS,
    AV_CODEC_ID_ASS,
    AV_CODEC_ID_HDMV_TEXT_SUBTITLE,

    /* other specific kind of codecs (generally used for attachments) */
    AV_CODEC_ID_FIRST_UNKNOWN = 0x18000,           ///< A dummy ID pointing at the start of various fake codecs.
    AV_CODEC_ID_TTF = 0x18000,

    AV_CODEC_ID_BINTEXT    = 0x18800,
    AV_CODEC_ID_XBIN,
    AV_CODEC_ID_IDF,
    AV_CODEC_ID_OTF,
    AV_CODEC_ID_SMPTE_KLV,
    AV_CODEC_ID_DVD_NAV,
    AV_CODEC_ID_TIMED_ID3,
    AV_CODEC_ID_BIN_DATA,


    AV_CODEC_ID_PROBE = 0x19000, ///< codec_id is not known (like AV_CODEC_ID_NONE) but lavf should attempt to identify it

    AV_CODEC_ID_MPEG2TS = 0x20000, /**< _FAKE_ codec to indicate a raw MPEG-2 TS
                                * stream (only used by libavformat) */
    AV_CODEC_ID_MPEG4SYSTEMS = 0x20001, /**< _FAKE_ codec to indicate a MPEG-4 Systems
                                * stream (only used by libavformat) */
    AV_CODEC_ID_FFMETADATA = 0x21000,   ///< Dummy codec for streams containing only metadata information.
    AV_CODEC_ID_WRAPPED_AVFRAME = 0x21001, ///< Passthrough codec, AVFrames wrapped in AVPacket

	AV_CODEC_ID_JPEG,

};

typedef enum{
	ENUM_RECORD_TYPE_MOTION_DETECTED = 0,
	ENUM_RECORD_TYPE_ALL_TIME,
}RECORD_TYPE;



typedef enum{
	ENUM_IRCUT_MODE_AUTO = 0,		// auto mode
	ENUM_IRCUT_MODE_DAY,			// manual mode,day 
	ENUM_IRCUT_MODE_NIGHT,			// manuual mode,night
	ENUM_IRCUT_MODE_AUTO_BY_AE,     // auto mode : no AD ,use isp ae val;lifan@2021.07.19
	ENUM_IRCUT_MODE_TIMER,          // timer mode
}ENUM_IRCUT_MODE;

typedef enum{
    ENUM_WHITE_LIGHT_STATE_ON,
    ENUM_WHITE_LIGHT_STATE_OFF,
} ENUM_WHITE_LIGHT_STATE;

typedef enum{
	enum_image_normal = 0,
	enum_image_mirror,
	enum_image_flip,
	enum_image_mirror_flip,
}ENUM_IMAGE_MIRROR_FLIP_MODE;

typedef enum {
	ENUM_LANGUAGE_CN		= 0,
	ENUM_LANGUAGE_EN		= 1,
	ENUM_LANGUAGE_THA		= 2,
	ENUM_LANGUAGE_RUS       = 3,
}ENUM_LANGUAGE_TYPE;


enum {
	VOICE_PROMPT_STARTUP 	= 0x0000,
	VOICE_PROMPT_WIRE_CONNECT_SUCCEED,
	VOICE_PROMPT_WIRE_DISCONNECT,
	VOICE_PROMPT_WIRELESS_CONNECTING,
	VOICE_PROMPT_WIRELESS_CONNECT_SUCCEED,
	VOICE_PROMPT_WIRELESS_DISCONNECT,
	VOICE_PROMPT_RESET,
	VOICE_PROMPT_FIRST_BOOT,



	
	//////////////////////////////////////////////



	MEIAN_VOICE_PROMPT_DOOR_BELL,					// door_bell.pcm
	MEIAN_VOICE_PROMPT_RECV_INVALID_PARAM,			// vt_recv_error_params.pcm
	MEIAN_VOICE_PROMPT_PARAM_SAVED,					// save_success.pcm

	
	// sd card 
	MEIAN_VOICE_PROMPT_CARD_ERROR,					// card_error.pcm
	MEIAN_VOICE_PROMPT_CARD_FULL,					// card_full.pcm
	MEIAN_VOICE_PROMPT_CARD_LOST,					// card_lost.pcm
	MEIAN_VOICE_PROMPT_CARD_NOT_FORMAT,				// card_not_format.pcm
	MEIAN_VOICE_PROMPT_CARD_FORMAT_START,			// format_begin.pcm
	MEIAN_VOICE_PROMPT_CARD_FORMAT_FAILED,			// format_failed.pcm
	MEIAN_VOICE_PROMPT_CARD_FORMAT_SUCCESS,			// format_success.pcm
	

	//wireless device  match code.
	MEIAN_VOICE_PROMPT_ADD_FAILED,					// add_failed.pcm
	MEIAN_VOICE_PROMPT_ADD_START,					// add_start.pcm
	MEIAN_VOICE_PROMPT_ADD_SUCCESS,					// add_success.pcm

	// num 0 - 9, 10,100,1000
	MEIAN_VOICE_PROMPT_0,							// part_zero.pcm
	MEIAN_VOICE_PROMPT_1,							// part_one.pcm
	MEIAN_VOICE_PROMPT_2,							// part_two.pcm
	MEIAN_VOICE_PROMPT_3,							// part_three.pcm
	MEIAN_VOICE_PROMPT_4,							// part_four.pcm
	MEIAN_VOICE_PROMPT_5,							// part_five.pcm
	MEIAN_VOICE_PROMPT_6,							// part_six.pcm
	MEIAN_VOICE_PROMPT_7,							// part_seven.pcm
	MEIAN_VOICE_PROMPT_8,							// part_eight.pcm
	MEIAN_VOICE_PROMPT_9,							// part_nine.pcm
	MEIAN_VOICE_PROMPT_10,							// part_ten.pcm
	MEIAN_VOICE_PROMPT_100,							// part_hundred.pcm
	MEIAN_VOICE_PROMPT_1000,						// part_thousand.pcm

	// arm 
	MEIAN_VOICE_PROMPT_OUT_ARM,						// system_arm.pcm
	MEIAN_VOICE_PROMPT_DISCARD_ARM,					// system_dis_arm.pcm
	MEIAN_VOICE_PROMPT_HOME_ARM,					// system_home_stay.pcm
	MEIAN_VOICE_PROMPT_DING,						// ding.pcm 
	MEIAN_VOICE_PROMPT_ARMING_FAILED,				// arming_failed.pcm



	MEIAN_VOICE_PROMPT_STARTUP,						// device_start_success.pcm
	MEIAN_VOICE_PROMPT_RESET	,					// device_reset.pcm
	MEIAN_VOICE_PROMPT_DEEP_RESET,					// device_deep_reset.pcm

	
	MEIAN_VOICE_PROMPT_MCU_COMMUNICATION_ERROR,		// mcu_communica_error.pcm
	MEIAN_VOICE_PROMPT_MCU_HXB_READLY	,			// mcu_hxb_readly.pcm
	MEIAN_VOICE_PROMPT_MCU_INSIDE_READLY,			// mcu_inside_readly.pcm
	MEIAN_VOICE_PROMPT_MCU_XAN_READLY,				// mcu_xan_readly.pcm
	MEIAN_VOICE_PROMPT_MCU_LOST	,					// mcu_lost.pcm
	MEIAN_VOICE_PROMPT_MCU_RESUME	,				// mcu_resume.pcm
	
	MEIAN_VOICE_PROMPT_UPGRADE_FAILED	,			// upgrade_fail.pcm
	MEIAN_VOICE_PROMPT_UPGRADE_START	,			// upgrade_start.pcm
	MEIAN_VOICE_PROMPT_UPGRADE_SUCCESS	,			// upgrade_success.pcm
	
	MEIAN_VOICE_PROMPT_WIFI_CONFIG_SUCCESS	,		// wifi_config_success.pcm
	MEIAN_VOICE_PROMPT_WIFI_WAIT_TO_CONFIG	,		// wifi_config_wait.pcm
	MEIAN_VOICE_PROMPT_WIFI_CONNECT_SUCCESS	,		// wifi_connect_success.pcm
	MEIAN_VOICE_PROMPT_WIFI_CONNECT_WAIT	,		// wifi_connect_wait.pcm
	MEIAN_VOICE_PROMPT_NETWORK_CONNECT_SUCCESS	,	// net_connect_success.pcm


	MEIAN_VOICE_PROMPT_ARM_OBJ_WIRELESS_ZONE,				// part_wireless_zone.pcm
	MEIAN_VOICE_PROMPT_ARM_OBJ_BUS_ZONE,					// part_wired_bus_zone.pcm
	MEIAN_VOICE_PROMPT_ARM_OBJ_WIRED_ZONE,					// part_wired_zone.pcm
	MEIAN_VOICE_PROMPT_ARM_OBJ_REMOTE_CONTROLLER_ZONE,		// part_remote_controller.pcm
	MEIAN_VOICE_PROMPT_ARM_OBJ_ZONE,						// part_zone.pcm
	MEIAN_VOICE_PROMPT_ARM_OBJ_CHANNEL,						// part_channel.pcm
	MEIAN_VOICE_PROMPT_ARM_OBJ_SD_CARD,						// part_memory_card.pcm






	MEIAN_VOICE_PROMPT_ARM_EVENT_ARM_OUT,					// part_arm.pcm
	MEIAN_VOICE_PROMPT_ARM_EVENT_ARM_HOME,					// part_home_stay.pcm
	MEIAN_VOICE_PROMPT_ARM_EVENT_ARM_DISCARD,				// part_dis_arm.pcm
	MEIAN_VOICE_PROMPT_ARM_EVENT_ALARM_DELAY,				// part_delay_alarm.pcm
	MEIAN_VOICE_PROMPT_ARM_EVENT_ALARM_PERIMETER,			// part_perimeter_alarm.pcm
	MEIAN_VOICE_PROMPT_ARM_EVENT_ALARM_BURGLAR,				// part_burglar_alarm.pcm
	MEIAN_VOICE_PROMPT_ARM_EVENT_ALARM_EMERGENCY,			// part_emergency_alarm.pcm
	MEIAN_VOICE_PROMPT_ARM_EVENT_ALARM_24H,					// part_24h_alarm.pcm
	MEIAN_VOICE_PROMPT_ARM_EVENT_ALARM_FIRE,				// part_fire_alarm.pcm
	MEIAN_VOICE_PROMPT_ARM_EVENT_ALARM_MOTION_DETECT,		// part_motion_detection_alarm.pcm
	MEIAN_VOICE_PROMPT_ARM_EVENT_ALARM_DATA_ERROR,			// part_data_error_alarm.pcm
	MEIAN_VOICE_PROMPT_ARM_EVENT_ALARM_OUT_OF_MEMORY,		// part_out_of_memory_alarm.pcm
	MEIAN_VOICE_PROMPT_ARM_EVENT_ALARM_LOST,				// part_lost_alarm.pcm
	MEIAN_VOICE_PROMPT_ARM_EVENT_ALARM,						// part_alarm.pcm

	MEIAN_VOICE_PROMPT_DAO_JIAN_CHOU,                       // Daojianchou.pcm
	MEIAN_VOICE_PROMPT_WELCOME,                             // Welcome.pcm
	MEIAN_VOICE_PROMPT_GET_OUT_OF_HERE,                     // GetOutOfHere.pcm
	MEIAN_VOICE_PROMPT_ALARM_INFO_UPLOADED,                 // AlarmInfoUploaded.pcm

	MEIAN_VOICE_PROMPT_DJC_STARTUP,                         // DaojianchouStartup.pcm

	MEIAN_VOICE_PROMPT_ANNOUNCE_WIFI_IP,					// AnnounceDevIp.pcm "dev ip xxx.xxx.xxx.xxx"
	MEIAN_VOICE_PROMPT_IP_POINT,
	MEIAN_VOICE_PROMPT_WIFI_GET_IP_TIME_OUT,					// wifi get ip timeout...

	MEIAN_VOICE_PROMPT_BEEP,								// beep.pcm
	MEIAN_VOICE_PROMPT_PLEASE_SCAN_LOCATION_CODE,			// pleaseScanLocationCode.pcm
	MEIAN_VOICE_PROMPT_24H,									// RNA status green : 24h
	MEIAN_VOICE_PROMPT_48H,									// RNA status green : 48h
	MEIAN_VOICE_PROMPT_72H,									// RNA status green : 72h
	MEIAN_VOICE_PROMPT_RNA_GREEN_CODE,						// RNA Status : green (normal)
	MEIAN_VOICE_PROMPT_RNA_YELLOW_CODE,						// RNA Status : yellow (warn)
	MEIAN_VOICE_PROMPT_RNA_RED_CODE,						// RNA Status : red (alarm)
	MEIAN_VOICE_PROMPT_RNA_UNKONW,                                                                         // RNA Status :unknow (undefined)


	MEIAN_VOICE_PROMPT_ACCESS_WHITE_LIST_BASE = 0x1000,
	MEIAN_VOICE_PROMPT_ACCESS_CONTROLLER_DOOR_OPENED = MEIAN_VOICE_PROMPT_ACCESS_WHITE_LIST_BASE,				// hi3516dv300 double sensor access controller project
	MEIAN_VOICE_PROMPT_ACCESS_CONTROLLER_DOOR_CLOSED,
	MEIAN_VOICE_PROMPT_ACCESS_CONTROLLER_WELCOME,
	MEIAN_VOICE_PROMPT_ACCESS_CONTROLLER_GO_HOME,
	MEIAN_VOICE_PROMPT_ACCESS_CONTROLLER_CUSTOM_DEFINE,
	MEIAN_VOICE_PROMPT_ACCESS_WHITE_LIST_BUTT,

	MEIAN_VOICE_PROMPT_ACCESS_BLACK_LIST_BASE = 0x1100,
	MEIAN_VOICE_PROMPT_ACCESS_CONTROLLER_BLACK_LIST_VOICE = MEIAN_VOICE_PROMPT_ACCESS_BLACK_LIST_BASE,
	MEIAN_VOICE_PROMPT_ACCESS_CONTROLLER_BLACK_LIST_CUSTOM_DEFINE,
	MEIAN_VOICE_PROMPT_ACCESS_BLACK_LIST_BUTT,

	MEIAN_VOICE_PROMPT_ACCESS_STRANGER_BASE = 0x1200,
	MEIAN_VOICE_PROMPT_ACCESS_CONTROLLER_PLEASE_REGISTER = MEIAN_VOICE_PROMPT_ACCESS_STRANGER_BASE,
	MEIAN_VOICE_PROMPT_ACCESS_CONTROLLER_STRANGER_CUSTOM_DEFINE,
	MEIAN_VOICE_PROMPT_ACCESS_STRANGER_BUTT,


	MEIAN_VOICE_PROMPT_ACCESS_RF_QR_CODE_BASE = 0x1300,
	MEIAN_VOICE_PROMPT_ACCESS_QR_CODE_INVALID = MEIAN_VOICE_PROMPT_ACCESS_RF_QR_CODE_BASE,
	MEIAN_VOICE_PROMPT_ACCESS_RF_ADD_SUCCESSFULLY,
	MEIAN_VOICE_PROMPT_ACCESS_RF_HAS_ADDED,
	MEIAN_VOICE_PROMPT_ACCESS_RF_EDIT_SUCCESSFULLY,



	MEIAN_VOICE_PROMPT_IPC_BLACK_LIST_BASE = 0x1400,
	MEIAN_VOICE_PROMPT_IPC_BLACK_LIST = MEIAN_VOICE_PROMPT_IPC_BLACK_LIST_BASE,
	MEIAN_VOICE_PROMPT_IPC_WHITE_LIST,



	MEIAN_VOICE_PROMPT_BODY_TEMPERATURE_ABNORMAL = 0x1500,


	MEIAN_VOICE_PROMPT_QRJMF_MQTT_BROKER_ONLINE = 0x1600,
	MEIAN_VOICE_PROMPT_QRJMF_MQTT_BROKER_OFFLINE,

	MEIAN_VOICE_PROMPT_EBICYCLE_NO_ENTRY   = 0x1700,
	MEIAN_VOICE_PROMPT_ALERT_AREA          = 0x1701,

	MEIAN_VOICE_PROMPT_CUSTOM_DEFINE       = 0x1800,
	
	
};

#define CHECK_WHITE_LIST_VOICE_PROMPT(s) (((s) >= MEIAN_VOICE_PROMPT_ACCESS_WHITE_LIST_BASE) && ((s) < MEIAN_VOICE_PROMPT_ACCESS_WHITE_LIST_BUTT))
#define CHECK_BLACK_LIST_VOICE_PROMPT(s) (((s) >= MEIAN_VOICE_PROMPT_ACCESS_BLACK_LIST_BASE) && ((s) < MEIAN_VOICE_PROMPT_ACCESS_BLACK_LIST_BUTT))
#define CHECK_STRANGER_VOICE_PROMPT(s) (((s) >= MEIAN_VOICE_PROMPT_ACCESS_STRANGER_BASE) && ((s) < MEIAN_VOICE_PROMPT_ACCESS_STRANGER_BUTT))

#define CONFIG_ACCESS_VOICE_PROMPT_DIR CONFIG_FILE_DIR"AccessPrompt/"
#define CONFIG_WL_ACCESS_VOICE_PROMPT_FOR_CUSTOM CONFIG_ACCESS_VOICE_PROMPT_DIR"whitelist.pcm"
#define CONFIG_BL_ACCESS_VOICE_PROMPT_FOR_CUSTOM CONFIG_ACCESS_VOICE_PROMPT_DIR"blacklist.pcm"
#define CONFIG_STRANGER_ACCESS_VOICE_PROMPT_FOR_CUSTOM CONFIG_ACCESS_VOICE_PROMPT_DIR"stranger.pcm"

#define CONFIG_ALARM_VOICE_PROMPT_FOR_CUSTOME "/data/CustomDefine.pcm"



#define MAX_USER_ACCUNT_COUNT 8

#define PLAYBACK_VIDEO_MM_NAME "VideoPlay"
#define PLAYBACK_AUDIO_MM_NAME "AudioPlay"


#define VENC_MAIN_MM_NAME "VideoMain"
#define VENC_SUB_MM_NAME "VideoSub"
#define VENC_AUX_MAIN_MM_NAME "AuxVideoMain"
#define VENC_AUX_SUB_MM_NAME "AuxVideoSub"
#define VENC_MJPEG_MM_NAME "VideoMjpeg"
#define VENC_SNAPSHOT_MM_NAME "snapshot"
#define VENC_BODY_SNAPSHOT_MM_NAME "bodySnapshot"

#define AI_SHM_NAME "Ai"
#define AO_SHM_NAME "Ao"
#define VR_SHM_NAME "Vr"  //Voice Recognition
#define AUX_AI_SHM_NAME "AuxAi" // Double eye stream

#define AI_ALAW_SHM_NAME "AiAlaw"
#define AO_ALAW_SHM_NAME "AoAlaw"

#define AI_MM_NAME "AudioInput"
#define AO_MM_NAME "AudioOutput"

#define AUDIO_MM_BLOCK_SIZE 1024
#define AUDIO_MM_BLOCK_CNT	32
#define MAX_AUDIO_FRAME_CNT	32

#define AUDIO_INPUT_MM_BLK_SIZE AUDIO_MM_BLOCK_SIZE
#define AUDIO_INPUT_MM_BLK_CNT	AUDIO_MM_BLOCK_CNT
#define MAX_AUDIO_INPUT_FRAME_CNT MAX_AUDIO_FRAME_CNT


#define AUDIO_OUTPUT_MM_BLK_SIZE AUDIO_MM_BLOCK_SIZE
#define AUDIO_OUTPUT_MM_BLK_CNT	AUDIO_MM_BLOCK_CNT
#define MAX_AUDIO_OUTPUT_FRAME_CNT MAX_AUDIO_FRAME_CNT

#define MAX_AUDIO_FRAME_SIZE 4*1024


#define CONFIG_RECORD_FREE_SIZE (512*1024*1024)
#define CONFIG_MAX_RECORD_FILE_SIZE (256*1024*1024)
#define CONFIG_MAX_RECORD_TIME (15 * 60)
#define USE_FLV_MUXER 0
#define USE_AVI_MUXER 1

#ifdef CONFIG_USE_PROTOBUF_LITE_META_DATA
#define MEDIA_INFO_SHM_NAME "MediaInfo"
#define MEDIA_INFO_SHM_SIZE (512*1024)
#endif //#ifdef CONFIG_USE_PROTOBUF_LITE_META_DATA


#ifdef GK710X
#define MAIN_STREAM_SHM_SIZE (1024*1024)
#define SUB_STREAM_SHM_SIZE (256*1024)
#define MJPEG_STREAM_SHM_SIZE (1024*1024)
#define JPEG_STREAM_SHM_SIZE (256*1024)
#define VIDEO_CODEC_BUF_SIZE (256*1024)
#define PLAYBACK_VIDEO_SHM_SIZE (512*1024);
#define PLAYBACK_AUDIO_SHM_SIZE (32*1024);
#define VIDEO_CODEC_SUB_BUF_SIZE (96*1024)

#endif 

#ifdef HI3516DV100
#define MAIN_STREAM_SHM_SIZE (4*1024*1024)
#define SUB_STREAM_SHM_SIZE (1024*1024)
#define MJPEG_STREAM_SHM_SIZE (4*1024*1024)
#define JPEG_STREAM_SHM_SIZE (512*1024)
#define VIDEO_CODEC_BUF_SIZE (512*1024)
#define PLAYBACK_VIDEO_SHM_SIZE (1*1024*1024);
#define PLAYBACK_AUDIO_SHM_SIZE (64*1024);
#define VIDEO_CODEC_SUB_BUF_SIZE (256*1024)

#endif 

#ifdef HI3518EV100 
#define MAIN_STREAM_SHM_SIZE (1024*1024)
#define SUB_STREAM_SHM_SIZE (256*1024)
#define MJPEG_STREAM_SHM_SIZE (1024*1024)
#define JPEG_STREAM_SHM_SIZE (256*1024)

#define VIDEO_CODEC_BUF_SIZE (256*1024)
#define PLAYBACK_VIDEO_SHM_SIZE (512*1024);
#define PLAYBACK_AUDIO_SHM_SIZE (32*1024);
#define VIDEO_CODEC_SUB_BUF_SIZE (96*1024)

#endif 


#if defined(HI3518EV200)  || defined(FH8626)
#define MAIN_STREAM_SHM_SIZE (1024*1024)
#define SUB_STREAM_SHM_SIZE (256*1024)
#define MJPEG_STREAM_SHM_SIZE (1024*1024)
#define JPEG_STREAM_SHM_SIZE (256*1024)

#define VIDEO_CODEC_BUF_SIZE (256*1024)
#define PLAYBACK_VIDEO_SHM_SIZE (256*1024);
#define PLAYBACK_AUDIO_SHM_SIZE (32*1024);
#define VIDEO_CODEC_SUB_BUF_SIZE (96*1024)

#endif


#if defined(FH8852V200) || defined(FH8852V201) || defined(FH8852)
#define MAIN_STREAM_SHM_SIZE (1024*1024)
#define SUB_STREAM_SHM_SIZE (256*1024)
#define MJPEG_STREAM_SHM_SIZE (1024*1024)
#define JPEG_STREAM_SHM_SIZE (256*1024)

#define VIDEO_CODEC_BUF_SIZE (512*1024)
#define PLAYBACK_VIDEO_SHM_SIZE (512*1024);
#define PLAYBACK_AUDIO_SHM_SIZE (32*1024);
#define VIDEO_CODEC_SUB_BUF_SIZE (96*1024)

#endif


#ifdef SSC338 
#define MAIN_STREAM_SHM_SIZE (1024*1024)
#define SUB_STREAM_SHM_SIZE (256*1024)
#define MJPEG_STREAM_SHM_SIZE (1024*1024)
#define JPEG_STREAM_SHM_SIZE (256*1024)

#define VIDEO_CODEC_BUF_SIZE (256*1024)
#define PLAYBACK_VIDEO_SHM_SIZE (512*1024);
#define PLAYBACK_AUDIO_SHM_SIZE (32*1024);
#define VIDEO_CODEC_SUB_BUF_SIZE (96*1024)

#endif

#ifdef SSC335 
#define MAIN_STREAM_SHM_SIZE (1024*1024)
#define SUB_STREAM_SHM_SIZE (256*1024)
#define MJPEG_STREAM_SHM_SIZE (1024*1024)
#define JPEG_STREAM_SHM_SIZE (256*1024)

#define VIDEO_CODEC_BUF_SIZE (256*1024)
#define PLAYBACK_VIDEO_SHM_SIZE (512*1024);
#define PLAYBACK_AUDIO_SHM_SIZE (32*1024);
#define VIDEO_CODEC_SUB_BUF_SIZE (96*1024)

#endif


#ifdef MSC313E 
#define MAIN_STREAM_SHM_SIZE (1024*1024)
#define SUB_STREAM_SHM_SIZE (256*1024)
#define MJPEG_STREAM_SHM_SIZE (1024*1024)
#define JPEG_STREAM_SHM_SIZE (256*1024)

#define VIDEO_CODEC_BUF_SIZE (256*1024)
#define PLAYBACK_VIDEO_SHM_SIZE (512*1024);
#define PLAYBACK_AUDIO_SHM_SIZE (32*1024);
#define VIDEO_CODEC_SUB_BUF_SIZE (96*1024)

#endif

#ifdef MSC316DM 
#define MAIN_STREAM_SHM_SIZE   (8*1024*1024)
#define SUB_STREAM_SHM_SIZE    (256*1024)
#define MJPEG_STREAM_SHM_SIZE  (1024*1024)
#define JPEG_STREAM_SHM_SIZE   (256*1024)

#define VIDEO_CODEC_BUF_SIZE      (1024*1024)
#define PLAYBACK_VIDEO_SHM_SIZE   (1024*1024);
#define PLAYBACK_AUDIO_SHM_SIZE   (32*1024);
#define VIDEO_CODEC_SUB_BUF_SIZE  (96*1024)

#endif


#ifdef HI3516CV300
#define MAIN_STREAM_SHM_SIZE (2*1024*1024)
#define SUB_STREAM_SHM_SIZE (1024*1024)
#define MJPEG_STREAM_SHM_SIZE (1024*1024)
#define JPEG_STREAM_SHM_SIZE (256*1024)

#define VIDEO_CODEC_BUF_SIZE (512*1024)
#define PLAYBACK_VIDEO_SHM_SIZE (1024*1024);
#define PLAYBACK_AUDIO_SHM_SIZE (32*1024);
#define VIDEO_CODEC_SUB_BUF_SIZE (256*1024)

#endif


#if defined(HI3516EV200) || defined(HI3518EV300)
#define MAIN_STREAM_SHM_SIZE (1024*1024)
#define SUB_STREAM_SHM_SIZE (256*1024)
#define MJPEG_STREAM_SHM_SIZE (1024*1024)
#define JPEG_STREAM_SHM_SIZE (256*1024)

#define VIDEO_CODEC_BUF_SIZE (384*1024)
#define PLAYBACK_VIDEO_SHM_SIZE (512*1024);
#define PLAYBACK_AUDIO_SHM_SIZE (32*1024);
#define VIDEO_CODEC_SUB_BUF_SIZE (96*1024)

#endif


#if  defined(HI3516CV500) || defined(HI3516DV300)
#define MAIN_STREAM_SHM_SIZE (2*1024*1024)
#define SUB_STREAM_SHM_SIZE (512*1024)
#define MJPEG_STREAM_SHM_SIZE (1024*1024)
#define JPEG_STREAM_SHM_SIZE (256*1024)

#define VIDEO_CODEC_BUF_SIZE (768*1024)
#define PLAYBACK_VIDEO_SHM_SIZE (1024*1024);
#define PLAYBACK_AUDIO_SHM_SIZE (32*1024);
#define VIDEO_CODEC_SUB_BUF_SIZE (256*1024)
//////////////////////////////////////////////
// body detect version sdk

#define CONFIG_BODY_SNAPSHOT_JPEG_SHM_SIZE (1024*1024)
#define CONFIG_BODY_SNAPSHOT_JPEG_BUF_SIZE (768*1024)
#endif

#if  defined(SV823)
#define MAIN_STREAM_SHM_SIZE  (2*1024*1024)
#define SUB_STREAM_SHM_SIZE   (512*1024)
#define MJPEG_STREAM_SHM_SIZE (1024*1024)
#define JPEG_STREAM_SHM_SIZE  (1024*1024)

#define VIDEO_CODEC_BUF_SIZE     (768*1024)
#define PLAYBACK_VIDEO_SHM_SIZE  (1024*1024);
#define PLAYBACK_AUDIO_SHM_SIZE  (32*1024);
#define VIDEO_CODEC_SUB_BUF_SIZE (256*1024)
//////////////////////////////////////////////
// body detect version sdk

#define CONFIG_BODY_SNAPSHOT_JPEG_SHM_SIZE (1024*1024)
#define CONFIG_BODY_SNAPSHOT_JPEG_BUF_SIZE (768*1024)
#endif


#ifdef x86
#define MAIN_STREAM_SHM_SIZE (1024*1024)
#define SUB_STREAM_SHM_SIZE (256*1024)
#define MJPEG_STREAM_SHM_SIZE (1024*1024)
#define JPEG_STREAM_SHM_SIZE (256*1024)

#define VIDEO_CODEC_BUF_SIZE (256*1024)

#define PLAYBACK_VIDEO_SHM_SIZE (512*1024);
#define PLAYBACK_AUDIO_SHM_SIZE (32*1024);
#define VIDEO_CODEC_SUB_BUF_SIZE (256*1024)

#endif


#define AI_SHM_SIZE (64 * 1024)
#define AO_SHM_SIZE (64 * 1024)

#define AI_ENC_SHM_SIZE (32 * 1024)
#define AO_ENC_SHM_SIZE (32 * 1024)

enum{
	DATE_FMT_YYYY_MM_DD_HH_MM_SS = 0,
	DATE_FMT_HH_MM_SS_YYYY_MM_DD,
	DATE_FMT_YYYY_MM_DD_HH_MM_SS_AM_PM,
	DATE_FMT_ONLY_TITLE,

};


typedef enum{
	USER_PRIVILEGE_FACTORY  = 0,
	USER_PRIVILEGE_ADMIN,
	USER_PRIVILEGE_ORDINARY,
	USER_PRIVILEGE_VISITOR,
	USER_PRIVILEGE_DISABLED,
}USER_PRIVILEGE; // user privilege



typedef struct {
	uint32_t sampleRate;
	uint16_t bitWidth;
	uint16_t channel;
}__attribute__((packed))AUDIO_ATTR;

typedef struct{
	uint8_t luma;			//	[0,100]
	uint8_t constrast;		//	[0,100]
	uint8_t hue;			//	[0,100]
	uint8_t	saturation;		//	[0,100]
}__attribute__((packed))IMAGE_CSC_ATTR;


typedef enum{
	ENUM_ANTI_FLICKER_DISABLE 	= 0,
	ENUM_ANTI_FLICKER_50Hz		= 50,
	ENUM_ANTI_FLICKER_60Hz		= 60,
}ANTI_FLICKER_ATTR;


typedef struct{
	int mirror;
	int flip;
}__attribute__((packed))IMAGE_MIRROR_FLIP;

typedef struct{
	int enable;			// enc stream is enable?
	int stream_index;	// enc stream index
	int codec_id;		// enc codec id
    int width;			// enc frame width
	int heigh;			// enc frame height
    int isVBR;			// is vbr
    int frameRate;		// frame rate
    int bitRate;		// bitrate 
    int gop;			// P frames between two I frames
}__attribute__((packed))VIDEO_STRAM_INFO;




typedef struct{
    int32_t frameRate;		// frame rate
    int32_t resolution_w;	// width
	int32_t resolution_h;	// height
	int32_t rotate;			// 90 180 270
	int32_t luma;			// image brightness   	[0,100]
	int32_t contrast;		// image contrast		[0,100]
    int32_t hue;			// image hue			[0,100]
	int32_t saturation;		// image staturation	[0,100]
    int32_t sharpness;		// image sharpness		[0,100]
    int32_t mirror;			// image mirror	
    int32_t flip;			// image flip
    
    int32_t antiFlicker;	/*  0	:disable anti-flicker;
    					   50	:enable anti-flicker,power freq:50Hz
    					   60	:enable anti-flicker,power freq:60Hz
    					*/
    int32_t flag1;			// image flag1;(reserved)
	int32_t flag2;			// image flag2;(reserved)
	int32_t flag3;			// image flag3;(reserved)
	int32_t flag4;			// image flag4;(reserved)

}__attribute__((packed))VIDEO_INPUT_ATTR;


/*
	0: main stream;
	1: sub	stream;
	2: jpeg snapshot;
	3: mjpeg stream;
*/
enum{
	ENUM_STREAM_TYPE_MAIN	= 0,
	ENUM_STREAM_TYPE_SUB,
	ENUM_STREAM_TYPE_JPEG,
	ENUM_STREAM_TYPE_MJPEG,
	ENUM_STREAM_TYPE_COUNT,
};

typedef struct{
	int32_t enable;			// enc stream is enable?
	int32_t stream_index;	// enc stream index
	int32_t codec_id;		// enc codec id
    int32_t width;			// enc frame width
	int32_t heigh;			// enc frame height
    int32_t isVBR;			// is vbr
    int32_t frameRate;		// frame rate
    int32_t bitRate;		// bitrate 
    int32_t gop;			// P frames between two I frames
    int32_t reserved;		//just for align 8bytes;
	int32_t flag1;			// reserved flag1
	int32_t flag2;			// reserved flag2
	int32_t flag3;			// reserved flag3
	int32_t flag4;			// reserved flag4
}__attribute__((packed))VIDEO_ENC_STREAM_ATTR;

typedef struct{
	VIDEO_ENC_STREAM_ATTR stream[ENUM_STREAM_TYPE_COUNT];
}__attribute__((packed))VIDEO_ENC_ATTR;

typedef struct{
		VIDEO_STRAM_INFO stream[ENUM_STREAM_TYPE_COUNT];
}__attribute__((packed))VideoCodecEncInfo;





typedef struct{
	char 				name[256];
	int32_t				model;
	int32_t				sensorChip;
	int32_t				wifiChip;
	int32_t 			country;
	int32_t				supportSdCard;
	int32_t				supportCloudStorage;
	int32_t				supportPt;
	int32_t				supportZoom;
	int32_t				supportAF;
	int32_t				supportAudioCap;
	int32_t				supportTalk;
	int32_t				supportOnvif;
	int32_t				supportCgiCmd;
	int32_t				supportRtsp;
	int32_t				supportRtmp;
	int32_t				p2pPlatform;
	int32_t				flag1;
	int32_t				flag2;
	int32_t				flag3;
	int32_t				flag4;
}__attribute__((packed))PRODUCT_INFO;


typedef struct{
	char  			name[32];
	uint32_t		enable;
	uint32_t		dhcp;
	uint32_t		ip;
	uint32_t 		mask;
	uint32_t 		gw;
	uint32_t 		dns1;
	uint32_t		dns2;
	uint32_t 		reserved;
}__attribute__((packed))ETH_PARAM;

#define MAX_OSD_STRING_LEN 24

typedef struct{
	int32_t enable;
	int32_t enable_logo;
	int32_t date_fmt;
	uint32_t reserved;
	char  osd_string[MAX_OSD_STRING_LEN+1];
	uint8_t padding[3];
}__attribute__((aligned(4)))OSD_PARAM;


typedef struct{
	char ssid[64];
	char password[64];
}__attribute__((packed))WIFI_BASIC_ATTR;

typedef struct{
	char ssid[64];
	char intf[64];	
}__attribute__((packed))WIFI_INFO;



typedef struct{
	char  			name[32];
	uint32_t		enable;
	uint32_t		dhcp;
	uint32_t		ip;
	uint32_t 		mask;
	uint32_t 		gw;
	uint32_t 		dns1;
	uint32_t		dns2;
	uint32_t		reserved;
	char 			ssid[128];
	char			password[128];
//	uint32_t		wpa_version;	// not required,low leved model will scan ap info,and get this information  just support wpa1,wpa2,open,
//	int 			cipher; 		// not required aes,tkip,none...
//	int 			auth_suites;	//not required  psk etc..
	
}__attribute__((packed))WIFI_PARAM;



typedef struct{
	uint8_t enable;
	uint8_t link_on ;
	uint8_t dhcp_on ;
	uint8_t padding;
	uint32_t ip;
	uint32_t mask;
	uint32_t gw;
	uint32_t dns1;
	uint32_t dns2;
	uint8_t  mac[6];
	uint16_t pading2;	
}__attribute__((packed))ETH_STATUS;


typedef struct{
	char essid[128] ;
	uint8_t enable;
	uint8_t signal; //[0,100]
	uint8_t dhcp_on ;
	uint8_t padding;
	uint32_t ip;
	uint32_t mask;
	uint32_t gw;
	uint32_t dns1;
	uint32_t dns2;
	uint8_t mac[6];
	uint16_t pading2;
}__attribute__((packed))WIFI_STATUS;


typedef struct{
	ETH_STATUS 	eth;
	WIFI_STATUS	wifi;
	uint8_t other[64];
}__attribute__((packed))NETWORK_STATUS;

typedef struct{
	ETH_PARAM  eth;
	WIFI_PARAM wifi;
	uint8_t other[64];       //other[0] 0:todo Nothing  1:Config eth 2:Config wifi 3:Config and Reconnect Wifi
}__attribute__((packed))NETWORK_ATTR;



typedef struct{
	uint32_t has_sdcard;
	uint32_t reserved;
	uint64_t total_size;
	uint64_t used_size;
}__attribute__((packed))SDCARD_STATUS;



typedef struct{
	NETWORK_STATUS network;
	SDCARD_STATUS sd;
	uint8_t reserved[1024];
}__attribute__((packed))DEVICE_STATUS;



typedef struct{
	PRODUCT_INFO product;
}__attribute__((packed))DEVICE_INFO;



typedef struct{
	uint32_t h264_support:1;
	uint32_t h265_support:1;
	uint32_t mjpeg_support:1;
	uint32_t jpeg_support:1;
	uint32_t : 0;
	uint32_t reserved;
	uint32_t resolution_w_max;
	uint32_t resolution_h_max;
	uint32_t resolution_w_min;
	uint32_t resolution_h_min;
	uint32_t frame_rate_min;
	uint32_t frame_rate_max;


	uint32_t bitrate_max;
	uint32_t bitrate_min;

	
}__attribute__((packed))STREAM_CAP;


typedef struct{
	STREAM_CAP mainStream;
	STREAM_CAP subStream;
	STREAM_CAP snapshort;
	STREAM_CAP mjpeg;
}__attribute__((packed))VIDEO_CAP;


typedef struct{
	uint32_t sample_rate_8000_support:1;
	uint32_t sample_rate_12000_support:1;
	uint32_t sample_rate_11025_support:1;
	uint32_t sample_rate_16000_support:1;
	uint32_t sample_rate_22025_support:1;
	uint32_t sample_rate_24000_support:1;
	uint32_t sample_rate_32000_support:1;
	uint32_t sample_rate_44100_support:1;
	uint32_t sample_rate_48000_support:1;
	uint32_t :0;
	uint32_t g711a_support:1;
	uint32_t g711u_support:1;
	uint32_t adpcm_support:1;
	uint32_t amrnb_support:1;
	uint32_t amrwb_support:1;
	uint32_t aac_support:1;
	uint32_t mp3_support:1;
	uint32_t :0;
	uint32_t audio_support:1;
	uint32_t talk_support:1;
	uint32_t :0;
	uint32_t reserved;	
}__attribute__((packed))AUDIO_CAP;



typedef struct{
	uint32_t result;
	uint32_t reserved;
	VIDEO_CAP video;
	AUDIO_CAP audio;
}__attribute__((packed))DEVICE_CAPACITY;


#if 0
typedef struct{
	time_t  t;
	struct timezone  tz;
}__attribute__((packed))DEVICE_TIME;

#else
typedef struct{
	time_t  t;
	int32_t nGMTDiff;
}__attribute__((packed))DEVICE_TIME;


#endif







typedef enum{
	MOTION_DETECT_SENSITIVITY_VERY_LOW = 0,
	MOTION_DETECT_SENSITIVITY_LOW,	
	MOTION_DETECT_SENSITIVITY_MID, 
	MOTION_DETECT_SENSITIVITY_HIGH, 
	MOTION_DETECT_SENSITIVITY_VERY_HIGH, 
}MOTION_DETECT_SENSITIVITY;




typedef struct{
	int32_t ircut_mode; // ENUM_IRCUT_MODE_XXX
	int32_t reserved;
}__attribute__((packed))CMD_SET_IRCUT_MODE;

typedef struct{
	int32_t result;
	int32_t reserved;
}__attribute__((packed))CMD_SET_IRCUT_MODE_RESULT;


typedef struct{
	int32_t reserved; 
	int32_t reserved2;
}__attribute__((packed))CMD_GET_IRCUT_MODE;

typedef struct{
	int32_t result; // ENUM_IRCUT_MODE_XXX
	int32_t ircut_mode;
}__attribute__((packed))CMD_GET_IRCUT_MODE_RESULT;




typedef struct{
	int32_t reserved; 
	int32_t reserved2;
}__attribute__((packed))CMD_TEST_IRCUT_OPEN;


typedef struct{
	int32_t reserved; 
	int32_t reserved2;
}__attribute__((packed))CMD_TEST_IRCUT_CLOSE;

typedef struct{
	int32_t result; 
	int32_t reserved2;
}__attribute__((packed))CMD_TEST_IRCUT_OPEN_RESULT;


typedef struct{
	int32_t result; 
	int32_t reserved2;
}__attribute__((packed))CMD_TEST_IRCUT_CLOSE_RESULT;





typedef struct{
	int32_t reserved; 
	int32_t reserved2;
}__attribute__((packed))CMD_DEBUG_OPEN_TELNET;


typedef struct{
	int32_t reserved; 
	int32_t reserved2;
}__attribute__((packed))CMD_DEBUG_CLOSE_TELNET;

typedef struct{
	int32_t result; 
	int32_t reserved2;
}__attribute__((packed))CMD_DEBUG_OPEN_TELNET_RESULT;


typedef struct{
	int32_t result; 
	int32_t reserved2;
}__attribute__((packed))CMD_DEBUG_CLOSE_TELNET_RESULT;



typedef struct{
	int32_t reserved; 
	int32_t reserved2;
}__attribute__((packed))CMD_TEST_OPEN_AI_AO_LOOP;


typedef struct{
	int32_t reserved; 
	int32_t reserved2;
}__attribute__((packed))CMD_TEST_CLOSE_AI_AO_LOOP;

typedef struct{
	int32_t result; 
	int32_t reserved2;
}__attribute__((packed))CMD_TEST_OPEN_AI_AO_LOOP_RESULT;


typedef struct{
	int32_t result; 
	int32_t reserved2;
}__attribute__((packed))CMD_TEST_CLOSE_AI_AO_LOOP_RESULT;





typedef struct{
	int32_t reserved; 
	int32_t reserved2;
}__attribute__((packed))CMD_START_TEST_SDCARD_WRITE;


typedef struct{
	int32_t reserved; 
	int32_t reserved2;
}__attribute__((packed))CMD_STOP_TEST_SDCARD_WRITE;

typedef struct{
	int32_t result; 
	int32_t reserved2;
}__attribute__((packed))CMD_START_TEST_SDCARD_WRITE_RESULT;


typedef struct{
	int32_t result; 
	int32_t reserved2;
}__attribute__((packed))CMD_STOP_TEST_SDCARD_WRITE_RESULT;


typedef struct{
	int32_t result;			// ENUM_SDCARD_TEST_ERROR_XXXXXX,0: success, < 0: error code 
	int16_t readSpeed; 		// KB/S
	int16_t writeSpeed;		// KB/S
	uint64_t totalSize;
	uint64_t freeSize;
	uint64_t usedSize;
}__attribute__((packed))CMD_POST_SDCARD_TEST_RESULT_MSG;


typedef struct{
	uint32_t enable;
	uint32_t maxRunTime;
	uint32_t noMotionTime;
	uint32_t reserved;
}__attribute__((packed))AUTO_MAINTENANCE_ATTR;


typedef struct{
	int32_t reserved; 
	int32_t reserved2;
}__attribute__((packed))CMD_GET_AUTO_MAINTENANCE_ATTR;

typedef struct{
	int32_t result; 
	int32_t reserved2;
	AUTO_MAINTENANCE_ATTR attr;
}__attribute__((packed))CMD_GET_AUTO_MAINTENANCE_ATTR_RESULT;



typedef struct{
	AUTO_MAINTENANCE_ATTR attr;
}__attribute__((packed))CMD_SET_AUTO_MAINTENANCE_ATTR;

typedef struct{
	int32_t result; 
	int32_t reserved2;
}__attribute__((packed))CMD_SET_AUTO_MAINTENANCE_ATTR_RESULT;



enum{
	ENUM_SDCARD_TEST_ERROR_NONE 				= 0,
	ENUM_SDCARD_TEST_ERROR_SDCARD_NOT_FOUND 	= -1,
	ENUM_SDCARD_TEST_ERROR_SDCARD_NOT_FORMAT	= -2,
	ENUM_SDCARD_TEST_ERROR_SDCARD_READ_FAILED	= -3,
	ENUM_SDCARD_TEST_ERROR_SDCARD_WRITE_FAILED	= -4,
};



typedef struct{
	int32_t language;				//ENUM_LANGUAGE_TYPE
	int32_t CaptureVolume;
	int32_t PlaybackVolume;
	int32_t enableVoicePrompt;
}__attribute__((packed))AUDIO_MISC_ATTR;



typedef struct{
	AUDIO_MISC_ATTR attr;
}__attribute__((packed))CMD_SET_AUDIO_ATTR;

typedef struct{
	int32_t result;
	int32_t reserved;
}__attribute__((packed))CMD_SET_AUDIO_ATTR_RESULT;




typedef struct{
	int32_t reserved;
	int32_t reserved2;
}__attribute__((packed))CMD_GET_AUDIO_ATTR;



typedef struct{
	int32_t result;
	int32_t reserved;
	AUDIO_MISC_ATTR attr;
}__attribute__((packed))CMD_GET_AUDIO_ATTR_RESULT;







typedef struct{
	uint8_t debugLogSw;
	uint8_t reserved1;
	uint8_t reserved2;
	uint8_t reserved3;
	uint32_t reserved4;
}__attribute__((packed))DEBUG_LOG_STATUS;


typedef struct{
	int32_t reserved;
	int32_t reserved2;
}__attribute__((packed))CMD_GET_DEBUG_LOG_STATUS;



typedef struct{
	int32_t result;
	int32_t reserved;
	DEBUG_LOG_STATUS status;
}__attribute__((packed))CMD_GET_DEBUG_LOG_STATUS_RESULT;



typedef struct{
	DEBUG_LOG_STATUS status;
}__attribute__((packed))CMD_SET_DEBUG_LOG_STATUS;



typedef struct{
	int32_t result;
	int32_t reserved;
}__attribute__((packed))CMD_SET_DEBUG_LOG_STATUS_RESULT;



typedef struct{
	uint32_t AuthEnable;
	char id[128];
	char passowrd[128];
	char authServerDomain[4][128];
	uint32_t authServerIp[4];
	uint16_t authServerPort[4];
	uint32_t registerServerIp[2];
	uint16_t registerServerPort[2];
}__attribute__((packed))MEIAN_PLATFORM_SERVER_ATTR;

typedef struct 
{
	unsigned short			m_focus_sw;					// 0 : disable focus platform , 1 : enable focus platform
	char					m_MainRegDomain[48];		// focus platform server domain name or ip address.
	unsigned short			m_nMainRegPort;				// focus platform server port
	char					m_SubRegDomain[48];			// focus platform server2 domain name or ip address.
	unsigned short			m_nSubRegPort;				// focus platform server2 port
	char					deviceid[32];				// focus platform device id
	char					passwd[16];					// focus platform device id password
	unsigned short			m_heartbeat;				// focus platform heart beat
	unsigned char			m_AutoAuth;					// 0 -- use manual setting , 1 -- auto config by auth server...
	char					m_reserv[11];
}FOCUS_CENTER_PARA;

typedef struct{
	char firmware[128];
}MEIAN_ALARM_HOST_UPGRADE_INFO;



typedef struct{
	int32_t reserved;
}__attribute__((packed))MSG_ALARM_HOST_GET_PLATFORM_SERVER_ATTR_REQ;




typedef struct{
	int32_t result;
	MEIAN_PLATFORM_SERVER_ATTR platform;
}__attribute__((packed))MSG_ALARM_HOST_GET_PLATFORM_SERVER_ATTR_RESULT;

typedef struct{
	MEIAN_PLATFORM_SERVER_ATTR platform;
}MSG_BROADCAST_MEIAN_PLATFORM_SERVER_CHANGE;


typedef struct{
	char firmware[256];
}MSG_BROADCAST_MEIAN_ALARM_HOST_UPGRADE_INFO;

typedef struct{
	char url[1024];

	int force_upgrade;
	
	uint8_t AppVer1;
	uint8_t AppVer2;
	uint8_t AppVer3;
	uint8_t AppVer4;

	uint8_t SysVer1;
	uint8_t SysVer2;
	uint8_t SysVer3;
	uint8_t SysVer4;
	
}MSG_BROADCAST_OTA_UPGRADE_INFO;

typedef struct{
	MSG_BROADCAST_OTA_UPGRADE_INFO upgradeInfo;
	char    recvName[32];	
}MSG_BROADCAST_OTA_UPGRADE_INFO_EX;

typedef struct{
	int32_t failed; // -1
}MSG_BROADCAST_OTA_QUERY_FAILED;

typedef struct{
	int32_t failed; // -1
	char    recvName[32];	
}MSG_BROADCAST_OTA_QUERY_FAILED_EX;


typedef struct{
	int32_t result;// 0: success, -1: failed
}MSG_BROADCAST_OTA_DOWNLOAD_RESULT;

typedef struct{
	int32_t result;// 0: success, -1: failed
	char    recvName[32];
}MSG_BROADCAST_OTA_DOWNLOAD_RESULT_EX;



typedef struct{
	char md5[16];
	char model[48];
	uint8_t reserved[512 - 16 - 48];
}__attribute__((packed))MCU_UPGRADE_FIRMWARE_HEADER;




/*

typedef struct
{
	uint8_t u8Zone;
	uint8_t u8Area;
	uint8_t u8Event;
	uint8_t au8CID_Code[4];
}MCU_ALARM_INFO_S;

*/


#if 0


const CID_CODE nCidIndexCode[CID_LENGTH] =
{
    {USER_SOS_TYPE,			1,1,0,0},		//0.个人救护//				0.	"1100"
    {DELAY_TYPE,			1,1,3,4},		//1.延迟报警//				1."1134"
    {PERIMETER_TYPE,		1,1,3,1},		//2.周界报警//				2.	"1131"
    {ROBBER_TYPE,			1,1,3,2},		//3.防盗报警//				3.	"1132"
    {SOS_RESCUE_TYPE,		1,1,2,0},		//4.紧急报�?/				4.	"1120"
    {ALL_DAY_TYPE,			1,1,3,3},		//5.24小时报警//			5.	"1133"
    {FIRE_TYPE,				1,1,1,0},		//6.火警//					6.	"1110"
    {SPILT_TYPE,			1,1,3,7},		//7.拆开报警	//			7.
    {SENSOR_LOW_PW_TYPE,	1,3,8,4},		//8 传感器低压报�?/		8 
    {SENSOR_LOW_RENEW_TYPE,	3,3,8,4},		//9 传感器电压恢�?/		9 
    {SENSOR_LOSE_TYPE,		1,3,8,1},		//10 传感器丢失报�?/		10 
    {SYS_BATT_TROUBLE_TYPE,	1,3,0,2},		//11 电池故障//				11
    {SYS_AC_TROUBLE_TYPE,	1,3,0,1},		//12 AC故障//			12 
    {SYS_AC_TROUBLE_RENEW_TYPE,3,3,0,1},	//13 AC恢复//		13 
    {BYPASS_REPORT_TYPE,	1,5,7,0},		//14 旁路报告//				14 
    {TEL_LINE_TROUBLE_TYPE,	1,3,5,1},		//15 电话线故�?/			15
    {COMM_TEST_REPORT_TYPE,	1,6,0,2},		//16 通讯测试报告//			16
    {LOOP_TROUBLE_TYPE,		1,3,7,0},		//17 回路故障//				17
    {LOOP_TROUBLE_RENEW_TYPE,3,3,7,0},		//18 回路恢复//				18 
    {SYS_BATT_RENEW_TYPE,	3,3,0,2},		//19 电池恢复//			19 
    {COMM_TROUBLE_TYPE,		1,3,5,0},		//20 网络故障//				20 
    {BYPASS_RENEW_TYPE,		3,5,7,0},		//21 旁路恢复//				21 
    {ALARM_ANNUL_TYPE,		1,4,0,6},		//22 报警取消//				22
    {DISARM_REPORT_TYPE,	1,4,0,1},		//23 系统撤防//				23 
    {HOME_REPORT_TYPE,		3,4,4,1},		//24 在家布防//				24
    {AWAY_ARM_REPORT_TYPE,	3,4,0,1},		//25 离家布防//			25
    {PROGRA_AMEND_TYPE,		1,3,0,6},		//26 编程改动//				26 
    {AUTO_ARM_FAIL_TYPE,	1,4,5,5},		//27 自动布防失败//			27
    {TEL_LINE_RENEW_TYPE,	3,3,5,1},		//28 电话线恢�?/			28 
    {COMM_RENEW_TYPE,		3,3,5,0},		//29 通讯恢复//				29 
    {SENSOR_LOSE_RENEW_TYPE,3,3,8,1},		//30 传感器恢�?/		30 
    {DRIVE_OPEN_TYPE,		1,9,0,1},		//31 设备打开//				31
    {DRIVE_CLOSE_TYPE,		3,9,0,1},		//32 设备关闭 //		32    
    {GSM_SIM_OVERDUE_REPORT_TYPE,1,6,0,0},	//33 SIM过期  //		33 
    {USER_TEST_COMM_REPORT_TYPE,1,6,0,1},	//34 用户测试通讯报告//		34 
    {SPILT_RENEW_TYPE,		3,1,3,7},		//35 拆动恢复	//			35


    {DVR_TYPE,1,6,0,1},		        ///51 手动通讯测试报告
	{DVR_TYPE,9,9,9,6},             ///52 硬盘丢失 
	{DVR_TYPE,9,9,9,4},             ///53 视频丢失 
	{DVR_TYPE,9,9,9,9},             ///54 移动侦测
	{DVR_TYPE,9,9,9,5},             ///55 镜头遮挡 
	{DVR_TYPE,9,9,8,8},             ///56 硬盘�?
	{DVR_TYPE,9,9,9,7},             ///57 硬盘错误  
	{DVR_TYPE,9,9,9,1},             ///58 硬盘格式�? 
	{DVR_TYPE,3,9,9,4},             ///59 视频丢失恢复  
	{DVR_TYPE,3,9,9,5},             ///60 视频遮挡恢复  
	{DVR_TYPE,9,9,8,4},             ///61 安装视频丢失
	{DVR_TYPE,1,9,1,6},             ///62 门铃
	{DVR_TYPE,1,1,2,1}				///63 劫持
};




#endif

typedef struct{
	uint8_t u8Zone;
	uint8_t u8Area;
	uint8_t u8Event;
	uint8_t au8CID_Code[4]; // nCidIndexCode
}__attribute__((packed))MCU_ALARM_INFO_S;

typedef struct{
	uint8_t  u8Zone;
	uint8_t  u8Area;
	uint8_t  u8Event;
	uint8_t  au8CID_Code[4];
	char     name[256];
	uint16_t linkage;
	uint8_t  alarmType;
	uint8_t  devCtlType;
	uint8_t  devType;
	char     devId[10];
	int      alarmSoundType;
}__attribute__((packed))MCU_ALARM_INFO,MSG_BROADCAST_ALARM_INFO;


typedef struct{
	uint8_t code[3];
	uint8_t type;
}__attribute__((packed))WIRELESS_CODE_MATCH_RESULT;


typedef struct{
	char version[64];
}__attribute__((packed))MSG_BROADCAST_MCU_VERSION_MSG;



typedef struct{
	uint8_t index; // start with 1
	uint8_t reserved;
	uint16_t status;
}__attribute__((packed))ADD_ALARM_DEVICE_RESULT;


typedef struct{
	uint8_t code[3];
	uint8_t type;		// CONFIGS_UNDERLING_DEV_TYPE_XXXX
	uint16_t index;		// start with 1
	uint8_t alarm_type;
	uint8_t sound_type;
	uint32_t wl_type;   // CONFIGS_DEV_CONTRL_TYPE_RF,CONFIGS_DEV_CONTRL_TYPE_BUS,CONFIGS_DEV_CONTRL_TYPE_LINE
	char name[256];
}__attribute__((packed))ADD_ALARM_DEVICE_REQ;



typedef struct{
	int32_t result;
	ADD_ALARM_DEVICE_RESULT status;
}__attribute__((packed))MSG_ADD_ALARM_DEVICE_RESULT;


typedef struct{
	ADD_ALARM_DEVICE_REQ req;
}__attribute__((packed))MSG_ADD_ALARM_DEVICE_REQ;

typedef struct{
	uint32_t devno;
}__attribute__((packed))MSG_DEL_ALARM_DEVICE_REQ;

typedef struct{
	int32_t result;
}__attribute__((packed))MSG_DEL_ALARM_DEVICE_RESULT;


typedef struct{
	uint16_t index;
	uint8_t sub_dev_index;
	uint8_t on_off_status;  // 1 : on ; 0 : off
}SWITCH_CONTROL_PARAM;



typedef struct{
	SWITCH_CONTROL_PARAM param;
}__attribute__((packed))MSG_CONTROL_SWITCH_REQ;

typedef struct{
	int32_t result;
}__attribute__((packed))MSG_CONTROL_SWITCH_RESULT;


typedef struct{
	time_t start;
}MSG_QUERY_DOWNLOAD_FAILED_REQ;



typedef struct{
	int32_t result;
	char file[1024];
}MSG_QUERY_DOWNLOAD_FAILED_RESULT;


#define HDD_NUM (1)


typedef struct
{
	uint8_t u8AlarmType; //0: motion detected 1: video coverd  2 : Hard disk error 3 : video lost  4 motion detected for PIR
	uint8_t u8AlarmTimeBySeconds; // alarm time
	uint8_t u8CallUser; 
	uint8_t u8Bell; 
	uint8_t u8AlarmCh; 
                       
}MCU_MD_REQ_S;





typedef struct{
	uint16_t index;  // frame index;
	uint16_t size;	 // frame data size; must be 512...
}MCU_GET_FIRMWARE_REQ;

typedef struct{
	uint8_t u8year;
	uint8_t u8month;
	uint8_t u8day;
	uint8_t u8hour;
	uint8_t u8minute;
	uint8_t u8second;
	uint8_t u8week;
}MCU_GET_TIME_RESP;


typedef struct
{
	uint8_t disable;
}__attribute__((packed))ALARM_HOST_ALARM_PARAM;



typedef struct
{
	uint8_t u8ArmMode;  //2:home arm   3:out arm
	uint8_t u8Area;     //Area 1~4	
}__attribute__((packed))ALARM_HOST_ARM_ERR_INFO;


typedef struct
{
	char number[4][18]; 
	int  repeatCount;
	int  priority;
}__attribute__((packed))ALARM_HOST_USER_PHONE;


typedef struct
{
	int32_t reserved; 
}__attribute__((packed))MSG_GET_ALARM_USER_PHONE_REQ;


typedef struct
{
	int32_t result;
	ALARM_HOST_USER_PHONE userPhone;
}__attribute__((packed))MSG_GET_ALARM_USER_PHONE_RESULT;

typedef struct
{
	ALARM_HOST_USER_PHONE userPhone;
}__attribute__((packed))MSG_SET_ALARM_USER_PHONE_REQ;


typedef struct
{
	int32_t result;
}__attribute__((packed))MSG_SET_ALARM_USER_PHONE_RESULT;


typedef struct{
	char result[512];
}MSG_QR_CODE_SCANNING_RESULT;


typedef struct{
	uint32_t enable;
}MSG_QR_CODE_SCANNING_CTRL_REQ;



#define DEV_TYPE_CHN     (0x00000001)
#define DEV_TYPE_IPC     (0x00000200)
#define DEV_TYPE_HDD_NUM (HDD_NUM << 12)
#define DEV_TYPE_ZONE    (0x00300000)
#define DEV_TYPE_REMOTE_UPGRADE    (0x00020000)
#define DEV_TYPE_XML     (1 << 18)

#define DEV_CAPABILITIES_PAN     					(1<<8)
#define DEV_CAPABILITIES_TILT    					(1<<9)
#define DEV_CAPABILITIES_ZOOM    					(1<<10)
#define DEV_CAPABILITIES_MIC     					(1<<11)
#define DEV_CAPABILITIES_TALK    					(1<<12)
#define DEV_CAPABILITIES_SOUND_WAVE_CONFIG_WIFI     (1<<13)
#define DEV_CAPABILITIES_AP_CONFIG_WIFI    			(1<<14)
#define DEV_CAPABILITIES_WIRE    					(1<<15)
#define DEV_CAPABILITIES_WIFI  						(1<<16)
#define DEV_CAPABILITIES_SOUND_LIGHT_ALARM    		(1<<17)
#define DEV_CAPABILITIES_RECORD   				    (1<<18)
#define DEV_CAPABILITIES_ALARM_HOST  				(1<<19)

// IPC�����Ͷ���
// bit0 ~ bit7 Ϊͨ����
// bit8Ϊ         P                    
// bit9Ϊ         T
// bit10Ϊ        Z
// bit11Ϊ        Mic
// bit12Ϊ        Talk
// bit13Ϊ        Sound Wave config wifi
// bit14Ϊ        Ap config wifi 
// bit15Ϊ        wire
// bit16Ϊ        wifi
// bit17Ϊ        Sound Light Alarm
// bit18Ϊ	  	  record
// bit19Ϊ	      Alarm host
// bit20Ϊ
// bit21Ϊ
// bit22Ϊ
// bit23Ϊ
// bit24 ~ bit31 Ϊ�豸����


enum {
	ENUM_MEIAN_DEVICE_TYPE_RESOLUTION_1080P   =  0x5B000000 +DEV_TYPE_REMOTE_UPGRADE+DEV_TYPE_ZONE+DEV_TYPE_HDD_NUM+DEV_TYPE_IPC+DEV_TYPE_CHN+DEV_TYPE_XML,
	ENUM_MEIAN_DEVICE_TYPE_RESOLUTION_960P    =  0x5C000000 +DEV_TYPE_REMOTE_UPGRADE+DEV_TYPE_ZONE+DEV_TYPE_HDD_NUM+DEV_TYPE_IPC+DEV_TYPE_CHN+DEV_TYPE_XML,
	ENUM_MEIAN_DEVICE_TYPE_RESOLUTION_720P    =  0x5A000000 +DEV_TYPE_REMOTE_UPGRADE+DEV_TYPE_ZONE+DEV_TYPE_HDD_NUM+DEV_TYPE_IPC+DEV_TYPE_CHN+DEV_TYPE_XML,
	ENUM_MEIAN_DEVICE_TYPE_RESOLUTION_960X960 =  0x40000000 +DEV_TYPE_REMOTE_UPGRADE+DEV_TYPE_ZONE+DEV_TYPE_HDD_NUM+DEV_TYPE_IPC+DEV_TYPE_CHN+DEV_TYPE_XML,
	ENUM_MEIAN_MSC313E_DEVICE_TYPE_RESOLUTION_1080P  	=  0x91000000 +DEV_TYPE_REMOTE_UPGRADE+DEV_TYPE_ZONE+DEV_TYPE_HDD_NUM+DEV_TYPE_IPC+DEV_TYPE_CHN+DEV_TYPE_XML,
	ENUM_MEIAN_DEVICE_TYPE_RESOLUTION_1440X1440 		=  0x92000000 +DEV_TYPE_REMOTE_UPGRADE+DEV_TYPE_ZONE+DEV_TYPE_HDD_NUM+DEV_TYPE_IPC+DEV_TYPE_CHN+DEV_TYPE_XML,
	ENUM_MEIAN_DEVICE_TYPE_RESOLUTION_400W		 		=  0x93000000 +DEV_TYPE_REMOTE_UPGRADE+DEV_TYPE_ZONE+DEV_TYPE_HDD_NUM+DEV_TYPE_IPC+DEV_TYPE_CHN+DEV_TYPE_XML,
	ENUM_MEIAN_DEVICE_TYPE_RESOLUTION_200W_DOOR_BELL	=  0x94000000 +DEV_TYPE_REMOTE_UPGRADE+DEV_TYPE_ZONE+DEV_TYPE_HDD_NUM+DEV_TYPE_IPC+DEV_TYPE_CHN+DEV_TYPE_XML,
	ENUM_MEIAN_DEVICE_TYPE_RESOLUTION_500W              =  0x95000000 +DEV_TYPE_REMOTE_UPGRADE+DEV_TYPE_ZONE+DEV_TYPE_HDD_NUM+DEV_TYPE_IPC+DEV_TYPE_CHN+DEV_TYPE_XML,
	ENUM_MEIAN_DEVICE_TYPE_RESOLUTION_300W              =  0x96000000 +DEV_TYPE_REMOTE_UPGRADE+DEV_TYPE_ZONE+DEV_TYPE_HDD_NUM+DEV_TYPE_IPC+DEV_TYPE_CHN+DEV_TYPE_XML,
	ENUM_MEIAN_DEVICE_TYPE_RESOLUTION_4K                =  0x97000000 +DEV_TYPE_REMOTE_UPGRADE+DEV_TYPE_ZONE+DEV_TYPE_HDD_NUM+DEV_TYPE_IPC+DEV_TYPE_CHN+DEV_TYPE_XML,
	ENUM_MEIAN_DEVICE_TYPE_RESOLUTION_8K                =  0x98000000 +DEV_TYPE_REMOTE_UPGRADE+DEV_TYPE_ZONE+DEV_TYPE_HDD_NUM+DEV_TYPE_IPC+DEV_TYPE_CHN+DEV_TYPE_XML,
	ENUM_MEIAN_DEVICE_TYPE_IPC                          =  0x99000000 +DEV_TYPE_CHN,
	ENUM_MEIAN_DEVICE_TYPE_EXT_DEV						=  0x9f000000 +DEV_TYPE_REMOTE_UPGRADE+DEV_TYPE_ZONE+DEV_TYPE_HDD_NUM+DEV_TYPE_IPC+DEV_TYPE_CHN+DEV_TYPE_XML,
	ENUM_MEIAN_DEVICE_TYPE_AI_DEV						=  0xC8000000 +DEV_TYPE_REMOTE_UPGRADE+DEV_TYPE_ZONE+DEV_TYPE_HDD_NUM+DEV_TYPE_IPC+DEV_TYPE_CHN+DEV_TYPE_XML,
	ENUM_MEIAN_DEVICE_TYPE_AI_DEV_1						=  0xC9000000 +DEV_TYPE_REMOTE_UPGRADE+DEV_TYPE_ZONE+DEV_TYPE_HDD_NUM+DEV_TYPE_IPC+DEV_TYPE_CHN+DEV_TYPE_XML,

	ENUM_MEIAN_DEVICE_TYPE_MEIAN_AI_DEV					=  0xB8000000 +DEV_TYPE_REMOTE_UPGRADE+DEV_TYPE_ZONE+DEV_TYPE_HDD_NUM+DEV_TYPE_IPC+DEV_TYPE_CHN+DEV_TYPE_XML,
	ENUM_MEIAN_DEVICE_TYPE_MEIAN_AI_DEV_1				=  0xB9000000 +DEV_TYPE_REMOTE_UPGRADE+DEV_TYPE_ZONE+DEV_TYPE_HDD_NUM+DEV_TYPE_IPC+DEV_TYPE_CHN+DEV_TYPE_XML,
};

enum{
	ENUM_MEIAN_JSON_PRTOCOL_DEVICE_TYPE_IPC_1 = 0xC1,   // IPC
	ENUM_MEIAN_JSON_PRTOCOL_DEVICE_TYPE_IPC_2 = 0xC2,   // IPC + Built-in Alarm Host
	ENUM_MEIAN_JSON_PRTOCOL_DEVICE_TYPE_IPC_3 = 0xC3,   // IPC + External Alarm Host
	ENUM_MEIAN_JSON_PRTOCOL_DEVICE_TYPE_IPC_4 = 0xC4,   // Fish Eye Camera + Built-in Alarm Host

	ENUM_MEIAN_JSON_PRTOCOL_DEVICE_TYPE_IPC_5 = 0xC8,   // IPC + AI detect  
	ENUM_MEIAN_JSON_PRTOCOL_DEVICE_TYPE_IPC_6 = 0xC9,   // IPC + AI detect + Built-in Alarm Host 

	ENUM_MEIAN_JSON_PRTOCOL_DEVICE_TYPE_IPC_7 = 0xB8,   // IPC + AI detect  
	ENUM_MEIAN_JSON_PRTOCOL_DEVICE_TYPE_IPC_8 = 0xB9,   // IPC + AI detect + Built-in Alarm Host
};

typedef enum maCONFIGS_DEV_CONTRL_TYPE
{
	CONFIGS_DEV_CONTRL_TYPE_RF     = 0,
	CONFIGS_DEV_CONTRL_TYPE_ZIGBEE = 1,
	CONFIGS_DEV_CONTRL_TYPE_WIFI   = 2,
	CONFIGS_DEV_CONTRL_TYPE_FSK    = 3,
	CONFIGS_DEV_CONTRL_TYPE_ZA_IAS = 4,
	CONFIGS_DEV_CONTRL_TYPE_IR     = 5,
	CONFIGS_DEV_CONTRL_TYPE_BUS    = 6,
	CONFIGS_DEV_CONTRL_TYPE_LINE   = 7,
	CONFIGS_DEV_CONTRL_TYPE_VIDEO  = 8,
	CONFIGS_DEV_CONTRL_TYPE_SBUS   = 9,
	CONFIGS_DEV_CONTRL_TYPE_GPIO   = 10,
	CONFIGS_DEV_CONTRL_TYPE_CNT,
}CONFIGS_DEV_CONTRL_TYPE;


typedef enum maCONFIGS_UNDERLING_DEV_TYPE_E
{
	CONFIGS_UNDERLING_DEV_TYPE_SWITCH           = 0,
	CONFIGS_UNDERLING_DEV_TYPE_FIRE_SENSOR      = 1,
	CONFIGS_UNDERLING_DEV_TYPE_WARTER_SENSOR    = 2,
	CONFIGS_UNDERLING_DEV_TYPE_GAS_SENSOR       = 3,
	CONFIGS_UNDERLING_DEV_TYPE_MOV_SENSOR       = 4, 
	CONFIGS_UNDERLING_DEV_TYPE_REMOTE_CTL       = 5,
	CONFIGS_UNDERLING_DEV_TYPE_WLS_WARMING      = 6,
	CONFIGS_UNDERLING_DEV_TYPE_LIGHT            = 7,
	CONFIGS_UNDERLING_DEV_TYPE_CURTAIN          = 8,
	CONFIGS_UNDERLING_DEV_TYPE_TEMP             = 9,
	CONFIGS_UNDERLING_DEV_TYPE_DOOR_SENSOR      = 10,
	CONFIGS_UNDERLING_DEV_TYPE_RAY_SENSOR       = 11,
	CONFIGS_UNDERLING_DEV_TYPE_LOCK             = 12,
	CONFIGS_UNDERLING_DEV_TYPE_CO_SENSOR        = 13,
	CONFIGS_UNDERLING_DEV_TYPE_INFRADE_TRANSMIT = 14,
	CONFIGS_UNDERLING_DEV_TYPE_WIND_LIGHT_RAIN  = 15,
	CONFIGS_UNDERLING_DEV_TYPE_BACKGOUND_MUSIC  = 16,
	CONFIGS_UNDERLING_DEV_TYPE_PLUG             = 17,
	CONFIGS_UNDERLING_DEV_TYPE_E_WINDOW         = 18,
	CONFIGS_UNDERLING_DEV_TYPE_COLOR_LED        = 19,
	CONFIGS_UNDERLING_DEV_TYPE_LEVEL_LED        = 20,
	CONFIGS_UNDERLING_DEV_TYPE_COLOR_TEM_LED    = 21,
	CONFIGS_UNDERLING_DEV_TYPE_IAS_DEV          = 22,
	CONFIGS_UNDERLING_DEV_TYPE_IR_DEV           = 23,
	CONFIGS_UNDERLING_DEV_TYPE_IR_CONTROL       = 24,
	CONFIGS_UNDERLING_DEV_TYPE_EMERGENCY_BUTTOM = 25,
	CONFIGS_UNDERLING_DEV_TYPE_SENCE_SWITCH     = 26,
	CONFIGS_UNDERLING_DEV_TYPE_LED_LOOP         = 27,
	CONFIGS_UNDERLING_DEV_TYPE_LED_RAY          = 28,
	CONFIGS_UNDERLING_DEV_TYPE_FISH_FEED_DEV    = 29,
	CONFIGS_UNDERLING_DEV_TYPE_SENSOR           = 30,
	CONFIGS_UNDERLING_DEV_TYPE_FSK_RGB_LED      = 31,
	CONFIGS_UNDERLING_DEV_TYPE_IP_CAMERA        = 32,
	CONFIGS_UNDERLING_DEV_TYPE_DOOR_BELL        = 33,
	CONFIGS_UNDERLING_DEV_TYPE_KEY_BOARD        = 34,
	CONFIGS_UNDERLING_DEV_TYPE_VIBRATION        = 35,
	CONFIGS_UNDERLING_DEV_TYPE_GLASS_BREAK      = 36,
	CONFIGS_UNDERLING_DEV_TYPE_INDICATOR        = 37,
	CONFIGS_UNDERLING_DEV_TYPE_PATROL           = 38,
	CONFIGS_UNDERLING_DEV_TYPE_CARD_READER      = 39,
	CONFIGS_UNDERLING_DEV_TYPE_REPEATER         = 40,
	CONFIGS_UNDERLING_DEV_TYPE_UNOKOWN          = 41,
}CONFIGS_UNDERLING_DEV_TYPE_E;

/////////////////////////////////////////////////////////////////////////////////////////


typedef enum{
	enum_access_mode_face = 0,
	enum_access_mode_qr_code = 1,
	enum_access_mode_rf_id = 2,
}ENUM_ACCESS_MODE;



typedef enum{
	ENUM_SERIAL_BAUDRATE_1200 	= 1200,
	ENUM_SERIAL_BAUDRATE_2400	= 2400,
	ENUM_SERIAL_BAUDRATE_4800	= 4800,
	ENUM_SERIAL_BAUDRATE_9600	= 9600,
	ENUM_SERIAL_BAUDRATE_19200	= 19200,
	ENUM_SERIAL_BAUDRATE_38400	= 38400,
	ENUM_SERIAL_BAUDRATE_57600	= 57600,
	ENUM_SERIAL_BAUDRATE_115200	= 115200,
}SERIAL_BAUDRATE;






typedef enum{
	ENUM_SERIAL_DATABIT_5		= 5,
	ENUM_SERIAL_DATABIT_6		= 6,
	ENUM_SERIAL_DATABIT_7		= 7,
	ENUM_SERIAL_DATABIT_8		= 8,
}SERIAL_DATA_BITS;


typedef enum{
	ENUM_SERIAL_STOPBIT_1 		= 0,
	ENUM_SERIAL_STOPBIT_2		= 1,
}SERIAL_STOPBIT;

typedef enum{
	ENUM_SERIAL_PARITY_NONE 	= 0,
	ENUM_SERIAL_PARITY_ODD		= 1,
	ENUM_SERIAL_PARITY_EVEN		= 2,
}SERIAL_PARITY;






////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
/// This code copy from NVR project .
/// lifan @2021.03.24 STARTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
////////////////////////////////////////////////////////////////////




typedef struct{
	char name[16];
	char mountpoint[64];
	uint32_t mounted:1;
	uint32_t isWritable:1;
	uint32_t reserved:30;
	uint32_t fstype;
	uint64_t size;
	uint64_t free;
}__attribute__((packed))REMOVABLE_DISK_INSERT_REJECT_MSG,REMOVABLE_DISK_STATUS;



typedef struct{
	char devpath[16];	
	int32_t result;		// 0 : successfully, < 0 : failed
	int32_t reserved;
	int32_t reserved2;
	int32_t reserved3;
}__attribute__((packed))REMOVABLE_DISK_FORMAT_RESULT;




typedef struct{
	REMOVABLE_DISK_INSERT_REJECT_MSG msg;
}__attribute__((packed))SDK_BROADCAST_REMOVABLE_DISK_INSERT_REJECT_MSG;



typedef struct{
	uint32_t reserved;
	uint32_t reserved2;
}__attribute__((packed))SDK_GET_REMOVABLE_DISK_LIST_REQ;

#define CONFIG_MAX_REMOVABLE_DISK_COUNT 16


typedef struct{
	REMOVABLE_DISK_STATUS disk[CONFIG_MAX_REMOVABLE_DISK_COUNT];
	int32_t result;
	uint32_t count;
}__attribute__((packed))SDK_GET_REMOVABLE_DISK_LIST_RESP;



typedef struct{
	char disk[16][16]; // /dev/sda
	uint32_t count;
	uint32_t fstype;
	uint32_t sid;
	uint32_t reserved;
}__attribute__((packed))SDK_START_FORMAT_REMOVABLE_DISK_REQ;

typedef struct{
	int32_t result;
	uint32_t reserved;
}__attribute__((packed))SDK_START_FORMAT_REMOVABLE_DISK_RESP;



typedef struct{
	char devpath[16];	
	int32_t result;		// 0 : successfully, < 0 : failed
	int32_t reserved;
	int32_t reserved2;
	int32_t reserved3;
}__attribute__((packed))SDK_BROADCAST_REMOVABLE_DISK_FORMAT_RESULT;



////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
/// This code copy from NVR project .
/// lifan @2021.03.24 ENDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
////////////////////////////////////////////////////////////////////



enum {
	E_JSON_ALARM_DEV_CTRL_TYPE_ASK    = 0,
	E_JSON_ALARM_DEV_CTRL_TYPE_ZIGBEE = 1,
	E_JSON_ALARM_DEV_CTRL_TYPE_WIFI   = 2,
	E_JSON_ALARM_DEV_CTRL_TYPE_FSK    = 3,
	E_JSON_ALARM_DEV_CTRL_TYPE_RES_1  = 4,
	E_JSON_ALARM_DEV_CTRL_TYPE_RES_2  = 5,
	E_JSON_ALARM_DEV_CTRL_TYPE_ABUS   = 6,    //485 bus
	E_JSON_ALARM_DEV_CTRL_TYPE_LINE   = 7,    
	E_JSON_ALARM_DEV_CTRL_TYPE_ACAN   = 8,    //CAN bus
	E_JSON_ALARM_DEV_CTRL_TYPE_SBUS   = 9,    //single bus
	E_JSON_ALARM_DEV_CTRL_TYPE_OGPIO  = 10,   //external switch
	E_JSON_ALARM_DEV_CTRL_TYPE_INIO   = 11,   //built-in switch
};

enum {
	E_JSON_ALARM_DEV_TYPE_DOOR_SENSOR          = 0x01,
	E_JSON_ALARM_DEV_TYPE_PIR                  = 0x02,
	E_JSON_ALARM_DEV_TYPE_SMOKE_SENSOR         = 0x03,
	E_JSON_ALARM_DEV_TYPE_GAS_SENSOR           = 0x04,
	E_JSON_ALARM_DEV_TYPE_CO_SENSOR            = 0x05,
	E_JSON_ALARM_DEV_TYPE_TEMP_HUMIDITY_SENSOR = 0x06,
	E_JSON_ALARM_DEV_TYPE_REMOTE               = 0x07,
	E_JSON_ALARM_DEV_TYPE_WATER_SENSOR         = 0x08,
	E_JSON_ALARM_DEV_TYPE_GLASS_BREAK_SENSOR   = 0x09,
	E_JSON_ALARM_DEV_TYPE_WARNING              = 0x0A,
	E_JSON_ALARM_DEV_TYPE_KEYBOARD             = 0x0B,
	E_JSON_ALARM_DEV_TYPE_VIBRATION_SENSOR     = 0x0C,
	E_JSON_ALARM_DEV_TYPE_EMERGENCY_BUTTON     = 0x0D,
	E_JSON_ALARM_DEV_TYPE_SWITCH               = 0x0E,
	E_JSON_ALARM_DEV_TYPE_DOOR_BELL            = 0x0F,

	E_JSON_ALARM_DEV_TYPE_INFRARED_INTRUSION   = 0x1A, 
	E_JSON_ALARM_DEV_TYPE_INDICATOR            = 0x1B,
	E_JSON_ALARM_DEV_TYPE_PATROL               = 0x1C,
	E_JSON_ALARM_DEV_TYPE_CARD_READER          = 0x1D,
	E_JSON_ALARM_DEV_TYPE_CURTAIN              = 0x1E,
};



typedef enum{
	enum_rs485_direction_rx = 0,
	enum_rs485_direction_tx = 1,	
}ENUM_RS_485_DIRECTION;


typedef enum {
	ENUM_ALGO_OBJECT_LABEL_TYPE_FACE     = 1,
	ENUM_ALGO_OBJECT_LABEL_TYPE_HUMANOID = 2,
}ENUM_ALGO_OBJECT_LABEL_TYPE;



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __MISC_DATA_TYPE_H__ */








