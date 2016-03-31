#define SP_RANDMAX 2147483648

typedef struct {

} sp_rand;

uint32_t sp_rand(sp_data *sp)
{
    uint32_t val = (1103515245 * sp->rand + 12345) % SP_RANDMAX;
    sp->rand = val;
    return val;
}

void sp_srand(sp_data *sp, uint32_t val)
{
    sp->rand = val;
}
uint32_t sp_rand(sp_data *sp);
void sp_srand(sp_data *sp, uint32_t val);
