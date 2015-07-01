#include <stdlib.h>
#include <jack/jack.h>
#include <unistd.h>
#include <aaio.h>
#include "soundpipe.h"

static jack_port_t *output_port;
static jack_client_t *client;

static int sp_jack_cb(jack_nframes_t nframes, void *arg)
{
    int i;
    jack_default_audio_sample_t  *out;
    sp_jack *jd = arg;
    out = jack_port_get_buffer (output_port, nframes);
    for(i = 0; i < nframes; i++){
        jd->callback(jd->sp, jd->ud);
        out[i] = jd->sp->out[0];
    }
    return 0;
}

void sp_jack_shutdown (void *arg)
{
    exit (1);
}

int sp_jack_process(sp_data *sp, void *ud, void (*callback)(sp_data *, void *))
{
    const char **ports;
    const char *client_name = "soundpipe";
    const char *server_name = NULL;
    jack_options_t options = JackNullOption;
    jack_status_t status;
    sp_jack jd;
    jd.sp = sp;
    jd.callback = callback;
    jd.ud = ud;

    client = jack_client_open (client_name, options, &status, server_name);
    if (client == NULL) {
        fprintf (stderr, "jack_client_open() failed, "
             "status = 0x%2.0x\n", status);
        if (status & JackServerFailed) {
            fprintf (stderr, "Unable to connect to JACK server\n");
        }
        exit (1);
    }
    if (status & JackServerStarted) {
        fprintf (stderr, "JACK server started\n");
    }
    if (status & JackNameNotUnique) {
        client_name = jack_get_client_name(client);
        fprintf (stderr, "unique name `%s' assigned\n", client_name);
    }
    jack_set_process_callback (client, sp_jack_cb, &jd);
    jack_on_shutdown (client, sp_jack_shutdown, 0);


    output_port = jack_port_register (client, "output",
                      JACK_DEFAULT_AUDIO_TYPE,
                      JackPortIsOutput, 0);

    if (output_port == NULL) {
        fprintf(stderr, "no more JACK ports available\n");
        exit (1);
    }

    if (jack_activate (client)) {
        fprintf (stderr, "cannot activate client");
        exit (1);
    }
    
    ports = jack_get_ports (client, NULL, NULL,
                JackPortIsPhysical|JackPortIsInput);
    if (ports == NULL) {
        fprintf(stderr, "no physical playback ports\n");
        exit (1);
    }

    if (jack_connect (client, jack_port_name (output_port), ports[0])) {
        fprintf (stderr, "cannot connect output ports\n");
    }

    free (ports);
    getch();
    jack_client_close (client);
    return SP_OK;
}
