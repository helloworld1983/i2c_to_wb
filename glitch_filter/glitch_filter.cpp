#include "systemc.h"
#include "glitch_filter.h"

void glitchFilter::tracing(sc_trace_file *tf)
{
    cout << "[VCD]" << "Add glitchFilter Signals to .VCD\n" << endl;
    const std::string str = this->name();
    
    // Dump local signals
    sc_trace(tf, this->in_reg, str+".in_reg");
    sc_trace(tf, this->buffer, str+".buffer");
    sc_trace(tf, this->all_hi_lsb, str+".all_hi_lsb");
    sc_trace(tf, this->all_low_lsb, str+".all_low_lsb");
    sc_trace(tf, this->out_en, str+".out_en");
    sc_trace(tf, this->temp_bit, str+".temp_bit");
}

/*
 * @fn  inSyncFlop()
 *
 * @details     Sync the input data with the master clock
*/
void glitchFilter::inSyncFlop(void)
{
    in_reg = in.read();
}

/*
 * @fn  filter()
 *
 * @details     Some sort of weird algorithm ...
*/
void glitchFilter::filter(void)
{
    buffer = (buffer.range(SIZE-2,0), in_reg);

    all_hi = (in_reg, buffer);              // Concatenate values
    all_hi_lsb = all_hi.and_reduce();       // AND reduction

    all_low = (in_reg, buffer);             // concatenate values
    all_low_lsb = all_low.nor_reduce();     // NOR reduction

    out_en = (all_hi_lsb & in_reg) | (all_low_lsb & ~in_reg);
}

/*
 * @fn  outputEnableToBuffer()
 *
 * @details     Set value for *out* output
*/
void glitchFilter::outputEnableToBuffer(void)
{
    if (out_en == true)
    {
        out.write( buffer.get_bit(SIZE-1) );
    }
}

/*
 * @fn  fallAndRise()
 *
 * @details     Set value for *fall* and *rise* outputs
*/
void glitchFilter::fallAndRise(void)
{
    temp_bit = all_low_lsb & out;
    fall.write(temp_bit.get_bit(0));

    temp_bit = all_hi_lsb & ~out;
    rise.write(temp_bit.get_bit(0));
}

