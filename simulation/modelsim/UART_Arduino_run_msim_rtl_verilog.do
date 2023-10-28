transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -sv -work work +incdir+C:/Users/linco/OneDrive/Desktop/S2Y3/MTRX3700/Major\ Project {C:/Users/linco/OneDrive/Desktop/S2Y3/MTRX3700/Major Project/uart_tx.sv}
vlog -sv -work work +incdir+C:/Users/linco/OneDrive/Desktop/S2Y3/MTRX3700/Major\ Project {C:/Users/linco/OneDrive/Desktop/S2Y3/MTRX3700/Major Project/uart_rx.sv}
vlog -sv -work work +incdir+C:/Users/linco/OneDrive/Desktop/S2Y3/MTRX3700/Major\ Project {C:/Users/linco/OneDrive/Desktop/S2Y3/MTRX3700/Major Project/top_level.sv}

vlog -sv -work work +incdir+C:/Users/linco/OneDrive/Desktop/S2Y3/MTRX3700/Major\ Project {C:/Users/linco/OneDrive/Desktop/S2Y3/MTRX3700/Major Project/uart_tb.sv}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cycloneive_ver -L rtl_work -L work -voptargs="+acc"  uart_tb

add wave *
view structure
view signals
run -all
