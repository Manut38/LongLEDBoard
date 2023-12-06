import {Notify} from 'quasar'

export default async ({app, router, Vue}) => {
  Notify.registerType('negative', {
    icon: 'eva-alert-circle-outline',
    color: 'negative',
    textColor: 'white'
  })
  Notify.registerType('positive', {
    icon: 'eva-checkmark-circle-2-outline',
    color: 'positive',
    textColor: 'white'
  })
  Notify.registerType('warning', {
    icon: 'eva-alert-triangle-outline',
    color: 'warning',
    textColor: 'black'
  })
  Notify.registerType('info', {
    icon: 'eva-info-outline',
    color: 'info',
    textColor: 'white'
  })
}
