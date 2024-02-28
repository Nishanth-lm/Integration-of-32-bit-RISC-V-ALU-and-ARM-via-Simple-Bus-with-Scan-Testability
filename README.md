# Integration of 32-bit RISC-V ALU and ARM via Simple Bus with Scan Testability

The model is implemented in systemC for the purpose of executing RISC-V Instructions by ARM via simple bus (TLM) with 32-bit registers. These Registers are Readable and Writeable by the ARM and ALU. Additionally, the model has a scan chain that is utilized to test the registers as per Design for testability methodologies.

Top Module: The Top module system’s components, which include the ARM core, Registers, ALU, and scan chain, communicate via a simple bus architecture. This design promotes efficient data sharing. The system stores data in registers, which are directly coupled to the ALU in a register-based design. The ALU conducts arithmetic and logical operations on data from registers, generating results that are returned to registers. Write operations include beginning data writes to certain registers, delivering opcode to decide ALU operations, and carrying out the desired operation. Read operations involve getting results from specific registers and reading flags indicating various circumstances such as zero and carry flags.

Simple Bus: In a system, a fundamental communication framework is established through a simple bus architecture featuring master and slave components. This bus, functioning as a data highway, consists of parallel wires that convey signals such as data, addresses, and control instructions. This communication protocol follows Transaction Level Model (TLM).

Scan Chain: The design includes debugger and 7 registers of 32-bit each. The data transmission considered is Parallel In Parallel Out (PIPO). During the test mode, 1-bit Test Data Input (TDI) is fed to each register to the LSB position. The register being 32-bit, TDI is then left shifted serially to MSB and Test Data Output (TDO) is fetched from each of the register’s MSB position. As TAP controller is not part of the implementation, standalone debugger is used to pass the TDI.

