using System;
using System.Collections.Generic;
using System.Collections;
using System.Windows.Forms;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Drawing.Design;


namespace TerraControl {

public class MyBindingList :  CollectionBase, IBindingList
{

  private ListChangedEventArgs resetEvent = new ListChangedEventArgs(ListChangedType.Reset, -1);
  private ListChangedEventHandler onListChanged;


  public Timerswitch this[int index] 
  {
	get 
	  {
            return (Timerswitch)(List[index]);
	  }
	set 
	  {
		List[index] = value;
	  }
  }

    public int Add (Timerswitch value) 
    {
	  return List.Add(value);
    }

    public Timerswitch AddNew() 
    {
	  return (Timerswitch)((IBindingList)this).AddNew();
    }

    public void Remove (Timerswitch value) 
    {
	  List.Remove(value);
    }

    
    protected virtual void OnListChanged(ListChangedEventArgs ev) 
    {
	  if (onListChanged != null) 
        {
		  onListChanged(this, ev);
        }
    }
    

    protected override void OnClear() 
    {
	  foreach (Timerswitch c in List) 
        {
        }
    }

    protected override void OnClearComplete() 
    {
	  OnListChanged(resetEvent);
    }

    protected override void OnInsertComplete(int index, object value) 
    {
	  Timerswitch c = (Timerswitch)value;
	  OnListChanged(new ListChangedEventArgs(ListChangedType.ItemAdded, index));
    }

    protected override void OnRemoveComplete(int index, object value) 
    {
	  Timerswitch c = (Timerswitch)value;
	  OnListChanged(new ListChangedEventArgs(ListChangedType.ItemDeleted, index));
    }

    protected override void OnSetComplete(int index, object oldValue, object newValue) 
    {
	  if (oldValue != newValue) 
        {

            
		  OnListChanged(new ListChangedEventArgs(ListChangedType.ItemAdded, index));
        }
    }
    
    // Called by Timerswitch when it changes.
    internal void TimerswitchChanged(Timerswitch cust) 
    {
        
	  int index = List.IndexOf(cust);
        
	  OnListChanged(new ListChangedEventArgs(ListChangedType.ItemChanged, index));
    }
    

    // Implements IBindingList.
    bool IBindingList.AllowEdit 
    { 
	  get { return true ; }
    }

    bool IBindingList.AllowNew 
    { 
	  get { return true ; }
    }

    bool IBindingList.AllowRemove 
    { 
	  get { return true ; }
    }

    bool IBindingList.SupportsChangeNotification 
    { 
	  get { return true ; }
    }
    
    bool IBindingList.SupportsSearching 
    { 
	  get { return false ; }
    }

    bool IBindingList.SupportsSorting 
    { 
	  get { return false ; }
    }


    // Events.
    public event ListChangedEventHandler ListChanged 
    {
        add 
		  {
            onListChanged += value;
		  }
        remove 
		  {
            onListChanged -= value;
		  }
    }

    // Methods.
    object IBindingList.AddNew() 
    {
	  Timerswitch c = new Timerswitch(this.Count);
	  List.Add(c);
	  return c;
    }


    // Unsupported properties.
    bool IBindingList.IsSorted 
    { 
	  get { throw new NotSupportedException(); }
    }

    ListSortDirection IBindingList.SortDirection 
    { 
	  get { throw new NotSupportedException(); }
    }


    PropertyDescriptor IBindingList.SortProperty 
    { 
	  get { throw new NotSupportedException(); }
    }


    // Unsupported Methods.
    void IBindingList.AddIndex(PropertyDescriptor property) 
    {
	  throw new NotSupportedException(); 
    }

    void IBindingList.ApplySort(PropertyDescriptor property, ListSortDirection direction) 
    {
	  throw new NotSupportedException(); 
    }

    int IBindingList.Find(PropertyDescriptor property, object key) 
    {
	  throw  new NotSupportedException(); 
    }

    void IBindingList.RemoveIndex(PropertyDescriptor property) 
    {
	  throw new NotSupportedException(); 
    }

    void IBindingList.RemoveSort() 
    {
	  throw new NotSupportedException(); 
    }

}
}