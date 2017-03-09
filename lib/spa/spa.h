int spa_open(sp_data *sp, sp_audio *spa, const char *name, int mode);
size_t spa_write_buf(sp_data *sp, sp_audio *spa, SPFLOAT *buf, uint32_t size);
size_t spa_read_buf(sp_data *sp, sp_audio *spa, SPFLOAT *buf, uint32_t size);
int spa_close(sp_audio *spa);
