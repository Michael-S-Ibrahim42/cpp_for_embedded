/* **************************************************************************************
**       Author      :	Michael S. Ibrahim
**       Date        :	March 08, 2022
**       Version     :	V01
**       SWC         :	STD_cRegister
**       Description :	header of the class STD_cRegister
** **************************************************************************************/
#ifndef _STD_CREGISTER_H
#define _STD_CREGISTER_H
  #include <iostream>
  /* Bit manipulation MACROS */
  #define GET_BIT(REG, BIT)             ((REG>>BIT)&1)
  /* specific used types */
  typedef enum
  {
    R=0,   /* Read Only */
    W,     /* Write Only */
    RW,    /* Read and Write */
    S      /* Reserved */
  }STD_tenuPermission;
  /* error return */
  typedef enum
  {
    Nok = 0,    /* Error */
    Ok          /* No Error */
  }STD_tenuError;
  
  template <class T>
  class STD_cRegister
  {
    private:
      T* Register;    /* Pointer to the register */
      STD_tenuPermission RegisterPermission;    /* Permission value of the whole register */
      T ReadBits;        /* Read only bits */
      T WriteBits;       /* write only bits */
      T ReservedBits;    /* Reserved bits */
    public:
      /* Parameterized Constructor */
      STD_cRegister(T* P_ptRegister, STD_tenuPermission Copy_enuRegisterPermission = RW);
      STD_tenuError STD_enuSetRegisterValue(T Copy_tValue);
      STD_tenuError STD_enuGetRegisterValue(T& R_rtValue);
      STD_tenuError STD_enuSetBit(std::uint8_t Copy_u8Bit);
      STD_tenuError STD_enuClearBit(std::uint8_t Copy_u8Bit);
      STD_tenuError STD_enuGetBit(std::uint8_t Copy_u8Bit, std::uint8_t& R_ru8BitValue);
      STD_tenuError STD_enuSetRegPer(STD_tenuPermission Copy_enuPermission);
      STD_tenuError STD_enuSetBitPer(std::uint8_t Copy_u8Bit, STD_tenuPermission Copy_enuPermission);
  };
  template <class T>
  STD_cRegister<T>::STD_cRegister(T* P_ptRegister, STD_tenuPermission Copy_enuRegisterPermission = RW)
  {
    Register = P_ptRegister;
    RegisterPermission = Copy_enuRegisterPermission;
    ReadBits = 0;
    WriteBits = 0;
    Reserved = 0;
  }/* STD_cRegister Constructor */
  
  template <class T>
  STD_tenuError STD_cRegister<T>::STD_enuSetRegisterValue(T Copy_tValue)
  {
    STD_tenuError Loc_enuError = Ok;
    if((RegisterPermission == W) || (RegisterPermission == RW))
    {
      if((ReadBits&Copy_tValue) || (ReservedBits&Copy_tValue))
      {
        Loc_enuError = Nok;
      }
      else
      {
        *Register = Copy_tValue;
      }
    }
    else
    {
      Loc_enuError = Nok;
    }
    
    return(Loc_enuError);
  }

  template <class T>
  STD_tenuError STD_cRegister<T>::STD_enuGetRegisterValue(T& R_rtValue)
  {
    STD_tenuError Loc_enuError = Ok;
    if((RegisterPermission == R) || (RegisterPermission == RW))
    {
      if(WriteBits || ReservedBits)
      {
        Loc_enuError = Nok;
      }
      else
      {
        R_rtValue = *(this->Register);
      }
    }
    else
    {
      Loc_enuError = Nok;
    }
    return(Loc_enuError);
  }
  
  template <class T>
  STD_tenuError STD_cRegister<T>::STD_enuSetBit(std::uint8_t Copy_u8Bit)
  {
    STD_tenuError Loc_enuError = Ok;
    if((RegisterPermission == W) || (RegisterPermission == RW))
    {
      if(((ReadBits>>Copy_u8Bit)&1) || ((ReservedBits>>Copy_u8Bit)&1))
      {
        Loc_enuError = Nok;
      }
      else
      {
        *(this->Register) |= (1<<Copy_u8Bit);
      }
    }
    else
    {
      Loc_enuError = Nok;
    }
    
    return(Loc_enuError);
  }/* STD_enuSetBit */
  
  template <class T>
  STD_tenuError STD_cRegister<T>::STD_enuClearBit(std::uint8_t Copy_u8Bit)
  {
    STD_tenuError Loc_enuError = Ok;
    if((RegisterPermission == W) || (RegisterPermission == RW))
    {
      if(((ReadBits>>Copy_u8Bit)&1) || ((ReservedBits>>Copy_u8Bit)&1))
      {
        Loc_enuError = Nok;
      }/* if */
      else
      {
        *(this->Register) &= ~(1<<Copy_u8Bit);
      }/* else */
    }/* if */
    else
    {
      Loc_enuError = Nok;
    }/* else */
    return(Loc_enuError);
  }/* STD_enuClearBit */
 
  template <class T>
  STD_tenuError STD_cRegister<T>::STD_enuGetBit(std::uint8_t Copy_u8Bit, std::uint8_t& R_ru8BitValue)
  {
    STD_tenuError Loc_enuError = Ok;
    if((RegisterPermission == R) || (RegisterPermission == RW))
    {
      if(((ReservedBits>>Copy_u8Bit)&1) || ((WriteBits>>Copy_u8Bit)&1))
      {
        Loc_enuError = Nok;
      }/* if */
      else 
      {
        R_ru8BitValue = ((*Register)>>Copy_u8Bit)&1;
      }/* else */
    }/* if */
    else
    {
      Loc_enuError = Nok;
    }/* else */
    return(Loc_enuError);
  }/* STD_enuGetBit */
  
  template <class T>
  STD_tenuError STD_cRegister<T>::STD_enuSetRegPer(STD_tenuPermission Copy_enuPermission);
  {
    STD_tenuError Loc_enuError = Ok;
    RegisterPermission = Copy_enuPermission;
    
    return(Loc_enuError);
  }/* STD_enuSetRegPer */
  
  template <class T>
  STD_tenuError STD_cRegister<T>::STD_enuSetBitPer(std::uint8_t Copy_u8Bit, STD_tenuPermission Copy_enuPermission);
  {
    STD_tenuError Loc_enuError = Ok;
    if(Copy_enuPermission == R)
    {
      ReadBits     |=  (1<<Copy_u8Bit);
      WriteBits    &= ~(1<<Copy_u8Bit);
      ReservedBits &= ~(1<<Copy_u8Bit);
    }/* if */
    else if(Copy_enuPermission == W)
    {
      ReadBits     &= ~(1<<Copy_u8Bit);
      WriteBits    |=  (1<<Copy_u8Bit);
      ReservedBits &= ~(1<<Copy_u8Bit);      
    }/* else if */
    else if(Copy_enuPermission == RW)
    {
      ReadBits     &= ~(1<<Copy_u8Bit);
      WriteBits    &= ~(1<<Copy_u8Bit);
      ReservedBits &= ~(1<<Copy_u8Bit);      
    }/* else if */ 
    else if(Copy_enuPermission == S)
    {
      ReadBits     &= ~(1<<Copy_u8Bit);
      WriteBits    &= ~(1<<Copy_u8Bit);
      ReservedBits |=  (1<<Copy_u8Bit);      
    }/* else if */    
    else
    {
      Loc_enuError = Nok;
    }/* else */
    
    return(Loc_enuError);
  }/* STD_enuSetBitPer */

#endif