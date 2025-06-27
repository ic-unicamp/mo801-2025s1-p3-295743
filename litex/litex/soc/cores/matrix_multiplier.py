from migen import *
from litex.soc.interconnect.csr import CSRStorage, CSRStatus, CSR
from litex.gen import * 


class MatrixMultiplier(LiteXModule): 
   def __init__(self):
       self.a_val_in = CSRStorage(32) 
       self.b_val_in = CSRStorage(32) 


       self.add_to_accum = CSR(1) 
       self.reset_accum  = CSR(1)


       self.accum_out    = CSRStatus(32)
       self.done_flag    = CSRStatus(1) 


       self.specials += Instance("matrix_multiplier", 
           i_clk=ClockSignal(),
           i_reset=ResetSignal(),


           i_a_val_in = self.a_val_in.storage,
           i_b_val_in = self.b_val_in.storage,


           i_add_to_accum = self.add_to_accum.re,
           i_reset_accum  = self.reset_accum.re,


           o_accum_out = self.accum_out.status,
           o_done_flag = self.done_flag.status
       )
       self.comb += [
           self.add_to_accum.re.eq(0), 
           self.reset_accum.re.eq(0) 
       ]
