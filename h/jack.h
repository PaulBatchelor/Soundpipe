typedef struct sp_jack{
    sp_data *sp;
    void *ud;
    void (*callback)(sp_data *, void *);
}sp_jack;
int sp_jack_process(sp_data *sp, void *ud, void (*callback)(sp_data *, void *));
