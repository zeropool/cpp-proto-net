//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

// Generated from: enum.proto
namespace entity
{
    [global::ProtoBuf.ProtoContract(Name=@"PosiDirectionType")]
    public enum PosiDirectionType
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"NET", Value=49)]
      NET = 49,
            
      [global::ProtoBuf.ProtoEnum(Name=@"LONG", Value=50)]
      LONG = 50,
            
      [global::ProtoBuf.ProtoEnum(Name=@"SHORT", Value=51)]
      SHORT = 51
    }
  
    [global::ProtoBuf.ProtoContract(Name=@"LegStatus")]
    public enum LegStatus
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"UNOPENED", Value=0)]
      UNOPENED = 0,
            
      [global::ProtoBuf.ProtoEnum(Name=@"IS_OPENING", Value=1)]
      IS_OPENING = 1,
            
      [global::ProtoBuf.ProtoEnum(Name=@"OPENED", Value=2)]
      OPENED = 2,
            
      [global::ProtoBuf.ProtoEnum(Name=@"IS_CLOSING", Value=3)]
      IS_CLOSING = 3,
            
      [global::ProtoBuf.ProtoEnum(Name=@"CLOSED", Value=4)]
      CLOSED = 4
    }
  
    [global::ProtoBuf.ProtoContract(Name=@"LimitPriceType")]
    public enum LimitPriceType
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"Last", Value=0)]
      Last = 0,
            
      [global::ProtoBuf.ProtoEnum(Name=@"Opposite", Value=1)]
      Opposite = 1
    }
  
    [global::ProtoBuf.ProtoContract(Name=@"CompareCondition")]
    public enum CompareCondition
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"GREATER_THAN", Value=0)]
      GREATER_THAN = 0,
            
      [global::ProtoBuf.ProtoEnum(Name=@"GREATER_EQUAL_THAN", Value=1)]
      GREATER_EQUAL_THAN = 1,
            
      [global::ProtoBuf.ProtoEnum(Name=@"LESS_THAN", Value=2)]
      LESS_THAN = 2,
            
      [global::ProtoBuf.ProtoEnum(Name=@"LESS_EQUAL_THAN", Value=3)]
      LESS_EQUAL_THAN = 3
    }
  
}