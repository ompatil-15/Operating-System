function login() {
    window.location.href = "./login.html";
}

function validate_credentials() {
    var username = document.getElementById("username").value;
    var password = document.getElementById("password").value;
    
    if (username == 'admin' && password == 'onceuponatime') {
        window.location.href = "options.html";
    }
    else{
        alert("Invalid Credentials");
    }

    return false;
} 

function updateCurrentTime() {
    var currentTime = new Date();
    var hours = currentTime.getHours();
    var minutes = currentTime.getMinutes();
    var seconds = currentTime.getSeconds();

    minutes = (minutes < 10) ? "0" + minutes : minutes; 
    seconds = (seconds < 10) ? "0" + seconds : seconds;

    var formattedTime = hours + ":" + minutes + ":" + seconds;
    document.getElementById("time").innerText = formattedTime;
}

setInterval(updateCurrentTime, 1000);
updateCurrentTime();

var options = {
    chart: {
      type: 'line',
      width: '100%',
      height: '60%',
    },
    colors: ['#FFFF00'],
    series: [{
      name: 'signups',
      data: [104,203,180,279,359,260,170,230,390,350,380,390]
    }],
    xaxis: {
      categories: [,5,,10,,15,,20,,25,,30],
      labels: {
        style: {
            colors: '#d4d1d1'
        }
      }
      
    },
    yaxis: {
        tickAmount: 2,
        labels: {
            style: {
                colors: '#d4d1d1'
            }
          }
    },
    toolbar: {
        show: false
    },
    stroke: {
        curve: 'smooth',
        width: [3]
    },
    dataLabels: {
        style: {
          colors: ['rgb(0,0,0)']
        }
    }   
  }
  
var chart = new ApexCharts(document.querySelector(".signups-chart"), options);
chart.render();

var options = {
    series: [{
      name: "Cohort 1",
      data: [45, 52, 38, 24, 33, 26, 21, 20, 6, 8, 15, 10]
    },
    {
      name: "Cohort 2",
      data: [35, 41, 62, 42, 13, 18, 29, 37, 36, 51, 32, 35]
    },
    {
      name: 'Cohort 3',
      data: [87, 57, 74, 79, 75, 38, 62, 47, 82, 56, 45, 47]
    }
  ],
    chart: {
    height: '100%',
    type: 'line',
    padding: 0,
    zoom: {
      enabled: false
    },
  },
  toolbar: {
    show: false
  },
  dataLabels: {
    enabled: false
  },
  stroke: {
    width: [3, 3, 3],
    curve: 'straight',
    dashArray: [0, 8, 5]
  },
   xaxis: {
    categories: ['Jan','Feb','Mar','Apr','May','Jun','Jul','Aug','Sep','Oct','Nov','Dec'],
    labels: {
        style: {
            colors: '#d4d1d1'
        }
      }
  },
  yaxis: {
    tickAmount: 3,
    labels: {
        style: {
            colors: '#d4d1d1'
        }
      } 
  },
  grid: {
    borderColor: '#f1f1f1',
  }, 
  legend: {
    show: false
  }
  };

  var chart = new ApexCharts(document.querySelector(".profit-chart"), options);
  chart.render();


  
var options = {
  series: [93,88  ],
  chart: {
  width: '100%',
  height: '200px',
  type: 'radialBar',
  toolbar: {
    show: true
  }
},
stroke: {
  lineCap: 'round',
  color: '#000'
},
plotOptions: {
  radialBar: {
    startAngle: 0,
    endAngle: 360,
      hollow: {
      margin: 0,
      size: '47%',
      background: '#16113a',
      position: 'front',
      dropShadow: {
        enabled: true,
        top: 3,
        left: 0,
        blur: 4,
        opacity: 0.24
      }
    },
    track: {
      background: '#fff',
      strokeWidth: '67%',
      margin: 0, 
      dropShadow: {
        enabled: true,
        top: -3,
        left: 0,
        blur: 4,
        opacity: 0.35
      }
    },

    dataLabels: {
      show: true,
      name: {
        show: false,
      },
      value: {
        formatter: function(val) {
          return parseInt(val);
        },
        color: '#d4d1d1',
        fontSize: '30px',
        show: true,
      }
    },
    
  }
},

};

  
var chart = new ApexCharts(document.querySelector("#csat-chart"), options);
chart.render();


// var options1 = {
//   chart: {
//     height: '200px',
//     type: "radialBar",
//   },
//   series: [97,91],
//   color: '#fff',  
//   plotOptions: {
//     radialBar: {
//       dataLabels: {
//         name: {
//           show: false
//         },
//         total: {
//           show: true, 
//           label: 'CSAT',
//         },  
//         value: {
//           color: '#fff',
//           fontSize: '25px',
//         }
//       }
//     }
//   },
//   stroke:{
//     lineCap: 'round'
//   },
  
// };

// new ApexCharts(document.querySelector("#csat-chart"), options1).render();
 