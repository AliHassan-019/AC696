
#include "application/audio_dec_app.h"
#include "app_config.h"
#include "audio_config.h"
#include "app_main.h"


//////////////////////////////////////////////////////////////////////////////
extern struct audio_decoder_task decode_task;
extern struct audio_mixer mixer;
extern struct audio_dac_hdl dac_hdl;

extern u32 audio_output_channel_num(void);

//////////////////////////////////////////////////////////////////////////////
const struct audio_dec_format_hdl decode_format_list[] = {
    {"wtg", AUDIO_CODING_G729},
    {"msbc", AUDIO_CODING_MSBC},
    {"sbc", AUDIO_CODING_SBC},
    {"mty", AUDIO_CODING_MTY},
    {"aac", AUDIO_CODING_AAC},
    {"mp3", AUDIO_CODING_MP3},
    {"wma", AUDIO_CODING_WMA},
    {"wav", AUDIO_CODING_WAV},
    {0, 0},
};

//////////////////////////////////////////////////////////////////////////////

int audio_dec_app_create_param_init(struct audio_dec_app_hdl *dec)
{
    dec->p_decode_task = &decode_task;
    dec->p_mixer = &mixer;
#if defined(CONFIG_MEDIA_DEVELOP_ENABLE)
    dec->out_ch_num = audio_output_channel_num();
#else
    dec->p_dac_hdl = &dac_hdl;
#endif
    return 0;
}

int audio_dec_file_app_create_param_init(struct audio_dec_file_app_hdl *file_dec)
{
    file_dec->format = decode_format_list;
    return 0;
}

int audio_dec_app_audio_state_switch(struct audio_dec_app_hdl *dec, u32 flag)
{
    u8 need_set_audio = 1;
    /* if ((dec->dec_mix) && (audio_mixer_get_ch_num(dec->p_mixer) > 1)) { */
    /* need_set_audio = 0; */
    /* } */
    if (app_audio_get_state() == APP_AUDIO_STATE_IDLE) {
        need_set_audio = 1;
    }
    if (need_set_audio) {
        if (flag == AUDIO_DEC_FILE_FLAG_AUDIO_STATE_MUSIC) {
            app_audio_state_switch(APP_AUDIO_STATE_MUSIC, get_max_sys_vol());
        } else {
#ifdef TCFG_WTONT_ONCE_VOL
            extern u8 get_tone_once_vol(void);
            app_audio_state_switch(APP_AUDIO_STATE_WTONE, get_tone_once_vol());
#else
            app_audio_state_switch(APP_AUDIO_STATE_WTONE, get_tone_vol());
#endif
        }
    }
    return 0;
}

int audio_dec_app_audio_state_exit(struct audio_dec_app_hdl *dec, u32 flag)
{
    u8 need_set_audio = 1;
    /* if ((dec->dec_mix) && (audio_mixer_get_ch_num(dec->p_mixer) > 1)) { */
    /* need_set_audio = 0; */
    /* } */
    /* if (app_audio_get_state() == APP_AUDIO_STATE_IDLE) { */
    /* need_set_audio = 1; */
    /* } */
    if (need_set_audio) {
        if (flag == AUDIO_DEC_FILE_FLAG_AUDIO_STATE_MUSIC) {
            app_audio_state_exit(APP_AUDIO_STATE_MUSIC);
        } else {
            app_audio_state_exit(APP_AUDIO_STATE_WTONE);
        }
    }
    return 0;
}

int audio_dec_file_app_init_ok(struct audio_dec_file_app_hdl *file_dec)
{
    audio_dec_app_audio_state_switch(file_dec->dec, file_dec->flag & AUDIO_DEC_FILE_FLAG_AUDIO_STATE_MASK);
    return 0;
}

int audio_dec_file_app_play_end(struct audio_dec_file_app_hdl *file_dec)
{
    audio_dec_app_audio_state_exit(file_dec->dec, file_dec->flag & AUDIO_DEC_FILE_FLAG_AUDIO_STATE_MASK);
    audio_dec_file_app_close(file_dec);
    return 0;
}

int audio_dec_sine_app_init_ok(struct audio_dec_sine_app_hdl *sine_dec)
{
    audio_dec_app_audio_state_switch(sine_dec->dec, sine_dec->flag & AUDIO_DEC_FILE_FLAG_AUDIO_STATE_MASK);
    return 0;
}
int audio_dec_sine_app_play_end(struct audio_dec_sine_app_hdl *sine_dec)
{
    audio_dec_app_audio_state_exit(sine_dec->dec, sine_dec->flag & AUDIO_DEC_FILE_FLAG_AUDIO_STATE_MASK);
    audio_dec_sine_app_close(sine_dec);
    return 0;
}

#if (!defined(CONFIG_MEDIA_DEVELOP_ENABLE))
void audio_dec_app_output_sr_set(struct audio_dec_app_hdl *dec)
{
    /* #if defined(CONFIG_CPU_BR23) */
    /* extern u32 audio_output_rate(int input_rate); */
    /* dec->src_out_sr = audio_output_rate(dec->src_out_sr); */
    /* #endif */
    if (dec->sample_rate == 0) {
        dec->sample_rate = dec->src_out_sr;
    }
}
#endif


//////////////////////////////////////////////////////////////////////////////
// test
#if 0
#include "tone_player.h"

void audio_dec_file_test(void)
{
    struct audio_dec_file_app_hdl *hdl;
    hdl = audio_dec_file_app_create(TONE_POWER_ON, 1);
    if (hdl) {
        audio_dec_file_app_open(hdl);
    }
    os_time_dly(2);
    hdl = audio_dec_file_app_create(TONE_POWER_OFF, 1);
    if (hdl) {
        audio_dec_file_app_open(hdl);
    }
    os_time_dly(300);
}

static const struct audio_sin_param sine_test[] = {
    /*{0, 1000, 0, 100},*/
    {200 << 9, 4000, 0, 100},
};
static const struct audio_sin_param sine_test1[] = {
    {450 << 9, 24960, 1, 16.667 * 512},
    {0, 16000, 0, 100},
};
void audio_dec_sine_test(void)
{
    struct audio_dec_sine_app_hdl *hdl;
    /* hdl = audio_dec_sine_app_create(SDFILE_RES_ROOT_PATH"tone/vol_max.sin", 1); */
    hdl = audio_dec_sine_app_create_by_parm(sine_test1, ARRAY_SIZE(sine_test1), 1);
    if (hdl) {
        audio_dec_sine_app_open(hdl);
    }
    os_time_dly(2);
    hdl = audio_dec_sine_app_create_by_parm(sine_test, ARRAY_SIZE(sine_test), 1);
    if (hdl) {
        audio_dec_sine_app_open(hdl);
    }
    /* os_time_dly(300); */
}

void audio_dec_usb_file_test(void)
{
    tone_play_stop();
    clk_set("sys", 192 * 1000000L);

    struct audio_dec_file_app_hdl *hdl;
    /* hdl = audio_dec_file_app_create("storage/udisk/C/1.mp3", 1); */
    hdl = audio_dec_file_app_create("storage/udisk/C/1.wav", 1);
    if (hdl) {
        audio_dec_file_app_open(hdl);
    }
    os_time_dly(2);
    /* hdl = audio_dec_file_app_create("storage/udisk/C/2.mp3", 1); */
    hdl = audio_dec_file_app_create("storage/udisk/C/2.wav", 1);
    if (hdl) {
        audio_dec_file_app_open(hdl);
    }
    os_time_dly(300);
}

#endif /*test*/


